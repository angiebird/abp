#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

class Loc
{
    protected:
        double x;
        double y;
    public:
        Loc(){x = 0; y = 0;}
        Loc(double xx, double yy){x = xx; y = yy;}

        double get_x()const{return x;}
        double get_y()const{return y;}

        int get_loc(double& xx, double& yy){xx = x; yy=y;}
        int set_loc(double xx, double yy){x = xx; y = yy;}

        Loc operator+=(const Loc& right);
        Loc operator/=(double n);

        int show(){printf("%f %f\n", x, y);}
};

Loc Loc::operator+=(const Loc& right)
{
    this->x += right.get_x();
    this->y += right.get_y();
}

Loc Loc::operator/=(double n)
{
    this->x /= n;
    this->y /= n;
}

Loc operator+(const Loc& left, const Loc& right)
{
    Loc result(left.get_x() + right.get_x(), left.get_y() + right.get_y());
    return result;
}

int abp_load_file(char* fileName, Loc* loc, int size)
{
    FILE* fr;
    fr = fopen(fileName, "r");
    char str[100];
    int i = 0;
    int x, y, t;
    while(fgets(str, 100, fr))
    {
        if(i < size)
        {
            sscanf(str, "%d,%d,%d",&x,&y,&t);
            loc[i].set_loc(x, y);
        }
        else
        {
            debug("loc size is not enough");
        }
        i++;
    }
}



class Vic: public Loc
{
    protected:
        double t;
    public:
        Vic(int xx, int yy, int tt){x = xx; y = yy; t = tt;}
        double get_t(){return t;}
        int set_t(int tt){t = tt;}
};

template <class T>
int dist(T a, T b)
{
    return sqrt((a.get_x() - b.get_x())*(a.get_x() - b.get_x()) + (a.get_y() - b.get_y())*(a.get_y() - b.get_y()));
}

template <class T>
int kmeans(T* data, int dataNum, T* ctr, int K)
{
    int nCtr[dataNum];
    int cnt[K];

    // random initialize K centers
    for(int j = 0; j < K; j++)
    {
        ctr[j] = data[rand()%dataNum];
    }

    for(int run = 0; run < 100; run++)
    {
        // find the nearest center for each point
        for(int i = 0; i < dataNum; i++)
        {
            nCtr[i] = 0;
            int optD = dist<T>(ctr[nCtr[i]], data[i]);
            for(int j = 0; j < K; j++)
            {
                int curD = dist<T>(ctr[j], data[i]);
                if(curD < optD)
                {
                    optD = curD;
                    nCtr[i] = j;
                }
            }
        }

        // update center
        for(int j = 0; j < K; j++)
        {
            ctr[j].set_loc(0, 0);
            cnt[j] = 0;
        }

        for(int i = 0; i < dataNum; i++)
        {
            ctr[nCtr[i]] += data[i];
            cnt[nCtr[i]]++;
        }

        for(int j = 0; j < K; j++)
        {
            ctr[j]/=cnt[j];
            //ctr[j].show();
        }
    }
}

int main()
{
    srand(time(NULL));

    int ctrSize = 5;
    Loc ctr[ctrSize];

    int vicSize = 300;
    Loc vic[vicSize];
    abp_load_file("vic.txt", vic, vicSize);

    kmeans<Loc>(vic, vicSize, ctr, ctrSize);

    /*
    for(int i = 0; i < vicSize; i++)
    {
        vic[i].show();
    }


    for(int j = 0; j<ctrSize; j++)
    {
        ctr[j].show();
    }
    */
}
