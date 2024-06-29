#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9 + 7;

// ask about addition of k1 k2 k3 k4 tp vx while computing the value of x

double f1(double x, double y)
{
    return -x * y;
}
double f2(double x, double y)
{
    return x * y - y - x;
}
// apply fehlberg for x,y,vx,vy and for the largest error use the step size control
// pass the vals individually for four different functions f1 f2 f3 f4

// hmax is 1/100 the time period of the orbit...thats where we start as the step size
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // a<= time <=b
    // TOL is the tolerance that we need mostky 1e-6

    double h, t0, x0, y0, vx0, vy0, TOL, limit;
    cin >> h >> t0 >> x0 >> y0 >> vx0 >> vy0 >> TOL >> limit;
    // mention the boundary of time using  a and b
    vector<vector<double>> Traj; // for storing the values of x y vx vy
    vector<double> vec(4);
    vec[0] = x0;
    vec[1] = y0;
    vec[2] = vx0;
    vec[3] = vy0;
    double x, y;
    vector<double> errors(4);
    double maxerror;
    bool flag = 1;

    while (limit--)
    {
        while (flag)
        {

            vector<double> val(4);
            x = vec[0];
            y = vec[1];
            // modify the values after step size control and after storing error
            double k1x, k1y, k1vx, k1vy;
            double k2x, k2y, k2vx, k2vy;
            double k3x, k3y, k3vx, k3vy;
            double k4x, k4y, k4vx, k4vy;
            double k5x, k5y, k5vx, k5vy;
            double k6x, k6y, k6vx, k6vy;
            // cout<<vec[0]<<" "<<vec[1]<<" "<<vec[2]<<" "<<vec[3]<<endl;
            // cout<<x<<" "<<y<<" "<<endl;

            k1x = h * vec[2];
            k1y = h * vec[3];
            k1vx = h * f1(x, y);
            k1vy = h * f2(x, y);
            // cout << k1x << " " << k1y << " " << k1vy << " " << k1vy << endl;

            k2x = h * (vec[2] + 0.5 * k1vx);
            k2y = h * (vec[3] + 0.5 * k1vy);
            k2vx = h * (f1(x + k1x, y + k1y));
            k2vy = h * (f2(x + k1x, y + k1y));

            k3x = h * (vec[2] + 3.0 * (k1x / 32.0) + 9.0 * (k2x / 32.0));
            k3y = h * (vec[3] + 3.0 * (k1y / 32.0) + 9.0 * (k2y / 32.0));
            k3vx = h * h * f1(x + 3.0 * (k1x / 32.0) + 9.0 * (k2x / 32.0), y + 3.0 * (k1y / 32.0) + 9 * (k2y / 32.0));
            k3vy = h * h * f2(x + 3.0 * (k1x / 32) + 9.0 * (k2x / 32), y + 3.0 * (k1y / 32.0) + 9.0 * (k2y / 32.0));

            k4x = h * (vec[2] + (1932.0 / 2197.0) * k1vx - (7200.0 / 2197.0) * k2vx + (7296.0 / 2197.0) * k3vx);
            k4y = h * (vec[3] + (1932.0 / 2197.0) * k1vy - (7200.0 / 2197.0) * k2vy + (7296.0 / 2197.0) * k3vy);
            k4vx = h * f1(x + (1932.0 / 2197.0) * k1x - (7200.0 / 2197.0) * k2x + (7296.0 / 2197.0) * k3x, y + (1932.0 / 2197.0) * k1y - (7200.0 / 2197.0) * k2y + (7296.0 / 2197.0) * k3y);
            k4vy = h * f2(x + (1932.0 / 2197.0) * k1x - (7200.0 / 2197.0) * k2x + (7296.0 / 2197.0) * k3x, y + (1932.0 / 2197.0) * k1y - (7200.0 / 2197.0) * k2y + (7296.0 / 2197.0) * k3y);

            k5x = h * (vec[2] + (439.0 / 216.0) * k1vx - 8 * k2vx + (3680.0 / 513.0) * k3vx - (845.0 / 4104.0) * k4vx);
            k5y = h * (vec[3] + (439.0 / 216.0) * k1vy - 8 * k2vy + (3680.0 / 513.0) * k3vy - (845.0 / 4104.0) * k4vy);
            k5vx = h * f1(x + (439.0 / 216.0) * k1x - 8 * k2x + (3680.0 / 513.0) * k3x - (845.0 / 4104.0) * k4x, y + (439.0 / 216.0) * k1y - 8 * k2y + (3680.0 / 513.0) * k3y - (845.0 / 4104.0) * k4y);
            k5vy = h * f2(x + (439.0 / 216.0) * k1x - 8 * k2x + (3680.0 / 513.0) * k3x - (845.0 / 4104.0) * k4x, y + (439.0 / 216.0) * k1y - 8 * k2y + (3680.0 / 513.0) * k3y - (845.0 / 4104.0) * k4y);

            k6x = h * (vec[2] - (8.0 / 27.0) * k1vx + 2.0 * k2vx - (3544.0 / 2565.0) * k3vx + (1859.0 / 4104.0) * k4vx - (11.0 / 40.0) * k5vx);
            k6y = h * (vec[3] - (8.0 / 27.0) * k1vy + 2 * k2vy - (3544.0 / 2565.0) * k3vy + (1859.0 / 4104.0) * k4vy - (11.0 / 40.0) * k5vy);
            k6vx = h * f1(x - (8.0 / 27.0) * k1x + 2 * k2x - (3544.0 / 2565.0) * k3x + (1859.0 / 4104.0) * k4x - (11.0 / 40.0) * k5x, y - (8.0 / 27.0) * k1y + 2 * k2y - (3544.0 / 2565.0) * k3y + (1859.0 / 4104.0) * k4y - (11.0 / 40.0) * k5y);
            k6vy = h * f2(x - (8.0 / 27.0) * k1x + 2 * k2x - (3544.0 / 2565.0) * k3x + (1859.0 / 4104.0) * k4x - (11.0 / 40.0) * k5x, y - (8.0 / 27.0) * k1y + 2 * k2y - (3544.0 / 2565.0) * k3y + (1859.0 / 4104.0) * k4y - (11.0 / 40.0) * k5y);

            errors[0] = (1.0 / h) * ((1.0 / 360.0) * k1x - (128.0 / 4275.0) * k3x - (2197.0 / 75240.0) * k4x + (1.0 / 50.0) * k5x + (2.0 / 55.0) * k6x);
            errors[1] = (1.0 / h) * ((1.0 / 360.0) * k1y - (128.0 / 4275.0) * k3y - (2197.0 / 75240.0) * k4y + (1.0 / 50.0) * k5y + (2.0 / 55.0) * k6y);
            errors[2] = (1.0 / h) * ((1.0 / 360.0) * k1vx - (128.0 / 4275.0) * k3vx - (2197.0 / 75240.0) * k4vx + (1.0 / 50.0) * k5vx + (2.0 / 55.0) * k6vx);
            errors[3] = (1.0 / h) * ((1.0 / 360.0) * k1vy - (128.0 / 4275.0) * k3vy - (2197.0 / 75240.0) * k4vy + (1.0 / 50.0) * k5vy + (2.0 / 55.0) * k6vy);

            maxerror = errors[0];
            // cout << vec[0] << " " << vec[1] << endl;
            // cout<<k1x<<" "<<k2x<<" "<<k3x<<" "<<k4x<<" "<<k5x<<" "<<k6x<<endl;

            for (int i = 1; i < 4; i++)
            {
                maxerror = max(maxerror, errors[i]);
            }
            // cout<<maxerror<<endl;

            if (maxerror <= TOL)
            {
                vec[0] += (25.0 / 216.0) * k1x + (1408.0 / 2565.0) * k3x + (2197.0 / 4104.0) * k4x - (1.0 / 5.0) * k5x;
                vec[1] += (25.0 / 216.0) * k1y + (1408.0 / 2565.0) * k3y + (2197.0 / 4104.0) * k4y - (1.0 / 5.0) * k5y;
                vec[2] += (25.0 / 216.0) * k1vx + (1408.0 / 2565.0) * k3vx + (2197.0 / 4104.0) * k4vx - (1.0 / 5.0) * k5vx;
                vec[3] += (25.0 / 216.0) * k1vy + (1408.0 / 2565.0) * k3vy + (2197.0 / 4104.0) * k4vy - (1.0 / 5.0) * k5vy;

                val[0] = vec[0];
                val[1] = vec[1];
                val[2] = vec[2];
                val[3] = vec[3];
                Traj.push_back(val);
                flag = false;
            }
            else
            { // change the value of h here using the formula
                double delta = (0.84) * pow(TOL / maxerror, 1 / 4);
                if (delta <= 0.1) // to ensure a huge or very minimal step change occur
                {
                    h = 0.1 * h;
                }
                else if (delta >= 4)
                {
                    h = 4 * h;
                }
                else
                {
                    h = delta * h;
                }
                flag = true;
            }
        }

        t0 += h;
        flag = true;
    }

    for (int i = 0; i < Traj.size(); i++)
    {
        for (int j = 0; j < Traj[0].size(); j++)
        {
            cout << Traj[i][j] << setprecision(15) << "\t";
        }
        cout << endl;
    }

    return 0;
}