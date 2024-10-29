#include <iostream>
#include <chrono>
#include <ctime>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

struct coord {
    int x;
    int y;

    coord() {
        x = 0; y = 0;
    }
    coord(int x1, int y1):
        x(x1), y(y1) {  };
};

coord operator + (coord x1, coord y1)
{
    return coord(x1.x + y1.x, x1.y + y1.y);
}

class board {
    public:
    int n;
    int **brd;
    int xmoves[8] = { -2,-1,1,2,2,1,-1,-2 };
    int ymoves[8] = { 1,2,2,1,-1,-2,-2,-1 };
    bool subg[4] = { 0, 0, 0, 0 };
    int number=1;
    int currentquad=-1;
    int subcount=0;
    coord initial;

    board(int n1):
        n(n1)
    {
        brd = new int*[n * n];
        for (int i = 0; i < n; i++) {
            brd[i] = new int[n];
            for (int j = 0; j < n; j++)
                brd[i][j] = -1;
        }
    }

    bool IsPosible(coord nc, int newn, coord inibrd) {
        //std::cout << "IsPosible x: " << 0 + inibrd.x << "\t" << newn + inibrd.x << std::endl;
        //std::cout << "IsPosible y: " << 0 + inibrd.y << "\t" << newn + inibrd.y << std::endl;
        if (nc.x >= 0 + inibrd.x && nc.x < newn + inibrd.x && nc.y >= 0 + inibrd.y && nc.y < newn + inibrd.y && brd[nc.x][nc.y] == -1)
            return true;
        return false;
    }

    int nPossibles(coord nc, int newn, coord inibrd) {
        int cont = 0;
        coord nc1(0, 0);
        for (int i = 0; i < 8; i++) {
            nc1.x = nc.x + xmoves[i];
            nc1.y = nc.y + ymoves[i];
            if (IsPosible(nc1,newn, inibrd))
                cont++;
        }
        return cont;
    }

    inline bool checkquad(coord coordini, int newn, coord inibrd) {
        switch (currentquad)
        {
        case -1:
            return 1;
            break;
        case 0:
            if (coordini.x >= inibrd.x + newn - 2 && subg[2] == 0) {
                subg[currentquad] = 1;
                currentquad = 2;
                return 1;
            }
            if (coordini.y >= inibrd.y + newn - 2 && subg[1] == 0) {
                subg[currentquad] = 1;
                currentquad = 1;
                return 1;
            }
            break;
        case 1:
            if (coordini.x >= inibrd.x + newn - 2 && subg[3] == 0) {
                subg[currentquad] = 1;
                currentquad = 3;
                return 1;
            }
            if (coordini.y < inibrd.y + 2 && subg[0] == 0) {
                subg[currentquad] = 1;
                currentquad = 0;
                return 1;
            }
            break;
        case 2:
            if (coordini.x < inibrd.x + 2 && subg[0] == 0) {
                subg[currentquad] = 1;
                currentquad = 0;
                return 1;
            }
            if (coordini.y > inibrd.y + newn - 2 && subg[3] == 0) {
                subg[currentquad] = 1;
                currentquad = 3;
                return 1;
            }
            break;
        case 3:
            if (coordini.x < inibrd.x + 2 && subg[1] == 0) {
                subg[currentquad] = 1;
                currentquad = 1;
                return 1;
            }
            if (coordini.y < inibrd.y + 2 && subg[2] == 0) {
                subg[currentquad] = 1;
                currentquad = 2;
                return 1;
            }
            break;
        }
        return 0;
    }

    inline bool checkquad2(coord coordini, int newn, coord inibrd) {
        switch (currentquad)
        {
        case -1:
            return 1;
            break;
        case 0:
            if (coordini.x >= inibrd.x + newn - 2 && subg[2] == 0) {
                if ((coordini.x == inibrd.x + newn - 1 && (coordini.x+coordini.y)%2==1) || (coordini.x == inibrd.x + newn - 2 && (coordini.x + coordini.y) % 2 == 0)) {
                    subg[currentquad] = 1;
                    currentquad = 2;
                    return 1;
                }
            }
            if (coordini.y >= inibrd.y + newn - 2 && subg[1] == 0) {
                if ((coordini.y == inibrd.y + newn - 1 && (coordini.x + coordini.y) % 2 == 0) || (coordini.y == inibrd.y + newn - 2 && (coordini.x + coordini.y) % 2 == 1)) {
                    subg[currentquad] = 1;
                    currentquad = 1;
                    return 1;
                }
            }
            break;
        case 1:
            if (coordini.x >= inibrd.x + newn - 2 && subg[3] == 0) {
                if ((coordini.x == inibrd.x + newn - 1 && (coordini.x + coordini.y) % 2 == 1) || (coordini.x == inibrd.x + newn - 2 && (coordini.x + coordini.y) % 2 == 0)) {
                    subg[currentquad] = 1;
                    currentquad = 3;
                    return 1;
                }
            }
            if (coordini.y < inibrd.y + 2 && subg[0] == 0) {
                if ((coordini.y == inibrd.y + 1 && (coordini.x + coordini.y) % 2 == 1) || (coordini.y == inibrd.y && (coordini.x + coordini.y) % 2 == 0)) {
                    subg[currentquad] = 1;
                    currentquad = 0;
                    return 1;
                }
            }
            break;
        case 2:
            if (coordini.x < inibrd.x + 2 && subg[0] == 0) {
                if ((coordini.x == inibrd.x + 1 && (coordini.x + coordini.y) % 2 == 0) || (coordini.x == inibrd.x && (coordini.x + coordini.y) % 2 == 1)) {
                    subg[currentquad] = 1;
                    currentquad = 0;
                    return 1;
                }
            }
            if (coordini.y > inibrd.y + newn - 2 && subg[3] == 0) {
                if ((coordini.y == inibrd.y + newn - 1 && (coordini.x + coordini.y) % 2 == 0) || (coordini.y == inibrd.y + newn - 2 && (coordini.x + coordini.y) % 2 == 1)) {
                    subg[currentquad] = 1;
                    currentquad = 3;
                    return 1;
                }
            }
            break;
        case 3:
            if (coordini.x < inibrd.x + 2 && subg[1] == 0) {
                if ((coordini.x == inibrd.x + 1 && (coordini.x + coordini.y) % 2 == 0) || (coordini.x == inibrd.x && (coordini.x + coordini.y) % 2 == 1)) {
                    subg[currentquad] = 1;
                    currentquad = 1;
                    return 1;
                }
            }
            if (coordini.y < inibrd.y + 2 && subg[2] == 0) {
                if ((coordini.y == inibrd.y + 1 && (coordini.x + coordini.y) % 2 == 1) || (coordini.y == inibrd.y && (coordini.x + coordini.y) % 2 == 0)) {
                    subg[currentquad] = 1;
                    currentquad = 2;
                    return 1;
                }
            }
            break;
        }
        return 0;
    }

    inline int abs(int x, int y) {
        if ((x - y) < 0)
            return -(x - y);
        return x - y;
    }

    int point(coord nc, coord inibrd, int newn) {
        switch (currentquad)
        {
        case 0:
            return abs(nc.x, inibrd.x) + abs(nc.y, inibrd.y);
        case 1:
            inibrd.y += newn;
            return abs(nc.x, inibrd.x) + abs(nc.y, inibrd.y);
        case 2:
            inibrd.x += newn;
            return abs(nc.x, inibrd.x) + abs(nc.y, inibrd.y);
        case 3:
            inibrd.y += newn;
            inibrd.x += newn;
            return abs(nc.x, inibrd.x) + abs(nc.y, inibrd.y);
        }
    }

    bool warnsdorff(coord &coordini, int newn, coord inibrd)
    {
        if (number >= newn * newn + ((newn*newn)*subcount)) {
            if (newn % 2 == 0) {
                if (checkquad(coordini, newn, inibrd))
                    return 1;
            }
            else {
                if (checkquad2(coordini, newn, inibrd))
                    return 1;
            }
            if (subcount == 3)
                return 1;
            return 0;
        }

        coord nc1(0, 0);
        bool visited[8] = { 0,0,0,0,0,0,0,0 };
        int it = 0,temp=0;


        coord n_xy(0,0);
        //int min = newn*newn*4;
        int min = 9;
        for (int j = 0; j < 8; j++) {
            for (int i = 0; i < 8; i++) {
                nc1.x = coordini.x + xmoves[i];
                nc1.y = coordini.y + ymoves[i];
                if (!IsPosible(nc1, newn, inibrd)) {
                    continue;
                }
                int temp = nPossibles(nc1, newn, inibrd);
                //int temp = (nc1.x - inibrd.x) + (nc1.y - inibrd.y);
                /*if (number < (newn / 2) + (number * subcount) && currentquad != -1)
                    temp = point(nc1, inibrd, newn);
                else
                    temp = nPossibles(nc1, newn, inibrd);*/
                if (min > temp && visited[i] == 0 && brd[nc1.x][nc1.y] == -1) {
                    n_xy = nc1;
                    min = temp;
                    it = i;
                }
            }
            if (min == 9)
                break;
            visited[it] = 1;
            //min = newn*newn*4;
            min = 9;
            brd[n_xy.x][n_xy.y] = number;
            //print();
            //std::cout << "\n\n\n\n";
            number++;
            if (warnsdorff(n_xy, newn, inibrd) == 1) {
                coordini = n_xy;
                return 1;
            }
            else {
                brd[n_xy.x][n_xy.y] = -1;
                number--;
            }
        }
        return 0;
    }

    void solve(coord inibrd, coord &nc, int newn)
    {
        if (newn > 4 && newn < 10) {
            warnsdorff(nc, newn, inibrd);
            return;
        }
        
        currentquad = startsub(nc);
        for (int i = 0; i < 4; i++) {
            //print();
            switch (currentquad) {
            case 0:
                solve(inibrd, nc, newn / 2);
                break;
            case 1:
                solve(coord(inibrd.x, inibrd.y + (newn / 2)), nc, newn / 2);
                break;
            case 2:
                solve(coord(inibrd.x + (newn / 2), inibrd.y), nc, newn / 2);
                break;
            case 3:
                solve(coord(inibrd.x + (newn / 2), inibrd.y + (newn / 2)), nc, newn / 2);
                break;
            }
            subcount++;
        }
    }

    inline int startsub(coord nc) {
        
        int temp = 0;
        if (nc.x >= n / 2)
            temp += 2;
        if (nc.y >= n / 2)
            return temp + 1;
        else
            return temp;
    }

    void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                std::cout << brd[i][j] << "\t";
            std::cout << "\n\n";
        }
    }
        
    ~board() {
        for (int i = 0; i < n; i++)
            delete[] brd[i];
        delete[] brd;
    }
};

long long horse_1(int n, int x, int y)
{
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    board mb(n);
    coord pc(x, y);
    mb.brd[pc.x][pc.y] = 0;
    mb.solve(coord(0,0), pc, n);   
    mb.print();

    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;
}

int main()
{
    std::cout << horse_1(14, 0, 0);
}
