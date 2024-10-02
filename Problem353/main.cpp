
// task description, see: https://projecteuler.net/problem=353

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <iomanip>
#include <fstream>
#include <chrono>

using namespace std;

const double epsilon = 0.0000000001;
const double pi = 3.1415926535897932384626433;
const double inf = numeric_limits<double>::infinity();
int r;

// for tiling the graph, gives performance boost of blockingFactor.
int blockingFactor = 50;
int blockSize = r/blockingFactor;
int blocks = 2*blockingFactor + 2;

struct vertex
{
    int index, x, y, z;     // the point in space
    double d;               // used for dijkstra's priority queue, distance to the starting vertex
};

// this is way too hard to read otherwise. Segmentation is used for tiling of the space, s.t. near neighbors can be found quickly
typedef vector<vector<vector<list<vertex*>*>>> segmentation;

// returns a list of all integer-coordinate points on the sphere with radius r and centre (0,0,0).
list<vertex> *buildGraph();

// computes the cost to travel from u to v
double cost(vertex u, vertex v);

struct vertexComp
{
    inline bool operator()(const vertex &v, const vertex &u)
    {
        return v.d > u.d;
    }
};

// returns a vector of distance-vectors by performing dijkstra on g,
// with the cost function specified by the task: 
void dijkstra(vertex g[], const size_t n, size_t start, size_t pred[], segmentation *s);

// build a segmentation of the graph <g>, tiling the vertices into blocks, for more neighbor-searching speed.
segmentation *segments(list<vertex> *g);

// returns the segment that <v> belongs to in a tiling.
vertex getSegment(const vertex *v);

// extract all neighbors of <v> in blocks next to <v>'s block in the segmentation <s>.
list<vertex*> *getNeighbors(vertex *v, segmentation *s);

// compute the final solution to the problem
void solve();

// check if the created graph makes any sense for r=1
void testSimpleSphere();

// run the solution for just the current r, and export the points of the shortest path to <filename>
void exportPoints(string filename);

// makes debugging easier
ostream &operator<<(ostream &os, vertex v);

// convert a list of vertices to an array

vertex *listToArray(list<vertex> *l);

int main()
{
    testSimpleSphere();

    solve();

    r = 1023;

    // exportPoints("r1023.txt");

    return 0;
}

list<vertex> *buildGraph()
{
    list<vertex> *g = new list<vertex>();

    int index = 0;

    // let the south pole be the first vertex!
    g->push_back((vertex) {index++, 0, 0, -r, inf});

    for(int z=0; z<=r-1; z++)
    {
        for(int x=0; x<=r; x++)
        {
            int yMin = sqrt(r*r - z*z - x*x) - 1;
            int yMax = yMin + 1;

            for(int y=yMin; y<=yMax; y++)
            {
                if(x*x + y*y + z*z == r*r)                              // check if it all fits
                {
                    g->push_back((vertex) {index++, x, y, z, inf});     // if so, add the vertex to the graph

                    if(x != 0)
                    {
                        g->push_back((vertex) {index++, -x, y, z, inf});

                        if(y != 0)
                        {
                            g->push_back((vertex) {index++, x, -y, z, inf});
                            g->push_back((vertex) {index++, -x, -y, z, inf});

                            if(z != 0)
                            {
                                g->push_back((vertex) {index++, x, y, -z, inf});
                                g->push_back((vertex) {index++, x, -y, -z, inf});
                                g->push_back((vertex) {index++, -x, y, -z, inf});
                                g->push_back((vertex) {index++, -x, -y, -z, inf});
                            }
                        }
                        else if(z != 0)
                        {
                            g->push_back((vertex) {index++, x, y, -z, inf});
                            g->push_back((vertex) {index++, -x, y, -z, inf});
                        }
                    }
                    else
                    {
                        if(y != 0)
                        {
                            g->push_back((vertex) {index++, x, -y, z, inf});

                            if(z != 0)
                            {
                                g->push_back((vertex) {index++, x, y, -z, inf});
                                g->push_back((vertex) {index++, x, -y, -z, inf});
                            }
                        }
                        else if(z != 0)
                        {
                            g->push_back((vertex) {index++, x, y, -z, inf});
                        }
                    }
                }
            }
        }
    }

    // let the north pole be the last vertex!
    g->push_back((vertex) {index++, 0, 0, r, inf});

    return g;
}

vertex getSegment(const vertex *v)
{
    int offset = r/blockSize;    // no negative indices exist for the negative coordinates
    int zCoo = (v->z/blockSize) + offset;
    int yCoo = (v->y/blockSize) + offset;
    int xCoo = (v->x/blockSize) + offset;

    return {0, (int) xCoo, (int) xCoo, (int) zCoo, 0};
}

list<vertex*> *getNeighbors(vertex *v, segmentation *s)
{
    vertex coo = getSegment(v);
    list<vertex*> *ns = new list<vertex*>();

    auto checkBounds = [] (int index) -> bool
    {
        return index >= 0 && index < blocks;
    };

    for(int i=-1; i<=1; i++)
    {
        int z = coo.z + i;
        if(checkBounds(z))
        {
            for(int j=-1; j<=1; j++)
            {
                int y = coo.y + j;
                if(checkBounds(y))
                {
                    for(int k=-1; k<=1; k++)
                    {
                        int x = coo.x + k;
                        if(checkBounds(x))
                        {
                            auto l = s->at(z).at(y).at(x);

                            if(l != nullptr)    // there might be empty blocks!
                                ns->insert(ns->end(), l->begin(), l->end());
                        }
                    }
                }
            }
        }
    }

    return ns;
}

segmentation *segments(list<vertex> *g)
{
    blockSize = r/blockingFactor;
    blocks = 2*blockingFactor + 3;
    segmentation *s = new segmentation(blocks);

    // initialization
    for(int z = 0; z<blocks; z++)
    {
        s->at(z) = vector<vector<list<vertex*>*>>(blocks);

        for(int y = 0; y<blocks; y++)
        {
            s->at(z).at(y) = vector<list<vertex*>*>(blocks);

            for(int x = 0; x<blocks; x++)
                s->at(z).at(y).at(x) = nullptr;
        }
    }
    
    for(auto it = g->begin(); it != g->end(); it++)
    {
        vertex coo = getSegment(to_address(it));

        if(s->at(coo.z).at(coo.y).at(coo.x) == nullptr)
            s->at(coo.z).at(coo.y).at(coo.x) = new list<vertex*>();

        s->at(coo.z).at(coo.y).at(coo.x)->push_back(to_address(it));
    }
    
    return s;
}

double cost(vertex u, vertex v)
{
    // This is just computing the angle of the two vectors, where angle * r is the distance on the moon surface
    double dotProduct = u.x * v.x + u.y * v.y + u.z * v.z;
    double normU = sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
    double normV = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    double angle = acos(dotProduct / (normU * normV));

    return pow(angle / pi, 2);
}

bool compareVertices(vertex u, vertex v)
{
    // do some reweighting alla A-star
    // by computing the potentials of u and v, which are just the squared distances to the north pole.
    double potU = u.x*u.x + u.y*u.y + (u.z - r)*(u.z - r);
    double potV = v.x*v.x + v.y*v.y + (v.z - r)*(v.z - r);

    return u.d + potU < v.d + potV;
}

void dijkstra(vertex g[], const size_t n, size_t start, size_t pred[] = nullptr, segmentation *s = nullptr)
{
    // this is necessary, since priority_queue doesn't support priority updates, so there will be duplicates
    bool done[n];

    for(size_t i=0; i<n; i++)
    {
        if(pred != nullptr)
            pred[i] = -1;
        
        done[i] = false;
    }

    // priority queue Q for dijkstra
    priority_queue<vertex, vector<vertex>, vertexComp> q;
    g[start].d = 0;
    q.push(g[start]);

    while(!q.empty())
    {
        vertex u;

        do
        {
            if(q.empty())           // the last vertices could all be duplicates
                return;

            u = q.top();
            q.pop();
        } while(done[u.index]);     // remove old duplicates

        done[u.index] = true;       // this vertex has it's final distance assigned
        g[u.index].d = u.d;         // so we should save it to the original

        if(u.z == r)                // early break when the final distance to the north pole is known
            break;
        
        // check if we can use the neighbors of a segmentation, or simply treat all vertices as neighbors.
        if(s == nullptr)
        {
            for(int i=0; i<n; i++)
            {
                if(u.index == i || done[i])     // don't consider u itself or vertices that are finished
                    continue;

                vertex &v = g[i];               // other than that, all vertices are neighbors.

                double c = cost(u, v);

                if(u.d + c < v.d)               // relax the edge
                {
                    if(pred != nullptr)
                        pred[i] = u.index;
                    
                    v.d = u.d + c;
                    q.push(v);
                }
            }
        }
        else
        {
            auto ns = getNeighbors(&u, s);

            for(vertex *v: *ns)
            {
                if(u.index == v->index || done[v->index])   // don't consider u itself or vertices that are finished
                    continue;
                
                double c = cost(u, *v);

                if(u.d + c < v->d)               // relax the edge
                {
                    if(pred != nullptr)
                        pred[v->index] = u.index;
                    
                    v->d = u.d + c;
                    q.push(*v);
                }
            }

            delete ns;
        }
    }
    
    return;
}

void testSimpleSphere()
{
    cout << endl << "running testSimpleSphere()..." << endl;

    r = 1;
    auto g = buildGraph();

    cout << "found " << g->size() << " vertices for the sphere:" << endl;

    for(vertex &v: *g)
        cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
    
    const int n = g->size();
    vertex *gg = listToArray(g);
    
    delete g;

    dijkstra(gg, n, 0);     // the south pole should always have index 0

    cout << "distance from south pole to north pole via shortest path: " << setprecision(10) << gg[n-1].d << endl;

    delete[] gg;
}

void solve()
{
    cout << endl << "running solve()..." << endl;

    double sum = 0;

    for(int n=1; n<=15; n++)
    {
        r = pow(2, n) - 1;

        auto g = buildGraph();

        cout << "for r = " << r << " buildGraph() found " << g->size() << " vertices for the sphere." << endl;

        const size_t s = g->size();
        vertex *gg = listToArray(g);

        segmentation *seg = nullptr;
        if(r >= 1000)
        {
            cout << "since r >= 1000, block tiling will be performed on the graph..." << endl;
            seg = segments(g);
        }
        else
            cout << "since r < 1000, block tiling will not be performed on the graph..." << endl;
        
        cout << "now running dijkstra..." << endl;
        auto t0 = chrono::high_resolution_clock::now();
        dijkstra(gg, s, 0);     // the south pole should always have index 0
        auto t1 = chrono::high_resolution_clock::now();

        cout << "elapsed time: " << chrono::duration_cast<chrono::seconds>(t1 - t0).count() << "s" << endl;

        delete g;

        double M = gg[s-1].d;

        cout << "M(" << r << ") = " << M << "." << endl << endl;

        sum += gg[s-1].d;

        delete[] gg;
    }

    cout << "The sum of the minimal cost paths, rounded to 10 decimal places, is: " << setprecision(15) << sum << "." << endl;
}

void exportPoints(string filename)
{
    cout << endl << "running exportPoints()..." << endl;

    auto g = buildGraph();

    cout << "for r = " << r << " buildGraph() found " << g->size() << " vertices for the sphere." << endl;

    const size_t s = g->size();
    vertex *gg = listToArray(g);

    size_t *predecessors = new size_t[s];

    segmentation *seg = nullptr;
    if(r >= 1000000000)
    {
        cout << "since r >= 1000, block tiling will be performed on the graph..." << endl;
        seg = segments(g);
    }
    else
        cout << "since r < 1000, block tiling will not be performed on the graph..." << endl;

    dijkstra(gg, s, 0, predecessors, seg);     // the south pole should always have index 0
    delete g;

    double M = gg[s-1].d;

    cout << "M(" << r << ") = " << M << "." << endl;

    ofstream ofs(filename);
    if(!ofs.good())
    {
        cout << "Could not open the file " << filename << ". Abort." << endl;
        return;
    }

    size_t i = s-1;
    while(i != -1)
    {
        vertex &v = gg[i];

        ofs << v.x << " " << v.y << " " << v.z << endl;

        i = predecessors[i];
    }

    delete[] gg;
    ofs.close();
}

ostream &operator<<(ostream &os, vertex v)
{
    cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

vertex *listToArray(list<vertex> *g)
{
    vertex *gg = new vertex[g->size()];
    
    auto it = g->begin();
    for(size_t i=0; i<g->size(); i++)
        gg[i] = *it++;
    
    return gg;
}
