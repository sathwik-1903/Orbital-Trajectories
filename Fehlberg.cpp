#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9 + 7;


// ask about addition of k1 k2 k3 k4 tp vx while computing the value of x 

double f1(double x, double y)
{
    double ans = x / sqrt(pow((x * x + y * y), 3));
    return ans;
}
double f2(double x, double y)
{
    double ans = y / sqrt(pow((x * x + y * y), 3));
    return ans;
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

    double h, t0, x0, y0, vx0, vy0, TOL,b;
    cin >> h >> t0 >> x0 >> y0 >> vx0 >> vy0 >> TOL>> b;
    // mention the boundary of time using  a and b
    vector<vector<double>> Traj; // for storing the values of x y vx vy
    vector<double> vec(4);
    vec[0] = x0;
    vec[1] = y0;
    vec[2] = vx0;
    vec[3] = vy0;
    double x, y;
    vector<double> errors(2);
    double maxerror;
    bool flag = 1;
    while (t0 <= b)
    {
        while (flag)
        {
            vector<double> val(4);
            x = vec[0];
            y = vec[1]; // errors for these is zero so no need to be considered
            // modify the values after step size control and after storing error
            vector<double> k1(2);
            vector<double> k2(2);
            vector<double> k3(2);
            vector<double> k4(2);
            vector<double> k5(2);
            vector<double> k6(2);

            k1[0] = h * f1(x, y);
            k2[0] = h * f1(x + k1[0] / 4, y + k1[0] / 4);
            k3[0] = h * f1(x + 3 * (k1[0] / 32) + 9 * (k2[0] / 32), y + 3 * (k1[0] / 32) + 9 * (k2[0] / 32));
            k4[0] = h * f1(x + (1932 / 2197) * k1[0] - (7200 / 2197) * k2[0] + (7296 / 2197) * k3[0], y + (1932 / 2197) * k1[0] - (7200 / 2197) * k2[0] + (7296 / 2197) * k3[0]);
            k5[0] = h * f1(x + (439 / 216) * k1[0] - 8 * k2[0] + (3680 / 513) * k3[0] - (845 / 4104) * k4[0], y + (439 / 216) * k1[0] - 8 * k2[0] + (3680 / 513) * k3[0] - (845 / 4104) * k4[0]);
            k6[0] = h * f1(x - (8 / 27) * k1[0] + 2 * k2[0] - (3544 / 2565) * k3[0] + (1859 / 4104) * k4[0] - (11 / 40) * k5[0], y - (8 / 27) * k1[0] + 2 * k2[0] - (3544 / 2565) * k3[0] + (1859 / 4104) * k4[0] - (11 / 40) * k5[0]);

            errors[0] = (1 / h) * ((1 / 360) * k1[0] - (128 / 4275) * k3[0] - (2197 / 75240) * k4[0] + (1 / 50) * k5[0] + (2 / 55) * k6[0]);

            k1[1] = h * f2(x, y);
            k2[1] = h * f2(x + k1[1] / 4, y + k1[1] / 4);
            k3[1] = h * f2(x + 3 * (k1[1] / 32) + 9 * (k2[1] / 32), y + 3 * (k1[1] / 32) + 9 * (k2[1] / 32));
            k4[1] = h * f2(x + (1932 / 2197) * k1[1] - (7200 / 2197) * k2[1] + (7296 / 2197) * k3[1], y + (1932 / 2197) * k1[1] - (7200 / 2197) * k2[1] + (7296 / 2197) * k3[1]);
            k5[1] = h * f2(x + (439 / 216) * k1[1] - 8 * k2[1] + (3680 / 513) * k3[1] - (845 / 4104) * k4[1], y + (439 / 216) * k1[1] - 8 * k2[1] + (3680 / 513) * k3[1] - (845 / 4104) * k4[1]);
            k6[1] = h * f2(x - (8 / 27) * k1[1] + 2 * k2[1] - (3544 / 2565) * k3[1] + (1859 / 4104) * k4[1] - (11 / 40) * k5[1], y - (8 / 27) * k1[1] + 2 * k2[1] - (3544 / 2565) * k3[1] + (1859 / 4104) * k4[1] - (11 / 40) * k5[1]);

            errors[1] = (1 / h) * ((1 / 360) * k1[1] - (128 / 4275) * k3[1] - (2197 / 75240) * k4[1] + (1 / 50) * k5[1] + (2 / 55) * k6[1]);

            maxerror = max(errors[0], errors[1]);

            if (maxerror <= TOL)
            {
                vec[0] = x + vec[2] * h;
                vec[1] = y + vec[3] * h;
                vec[2] += (25 / 216) * k1[0] + (1408 / 2565) * k3[0] + (2197 / 4104) * k4[0] - (1 / 5) * k5[0];
                vec[3] += (25 / 216) * k1[1] + (1408 / 2565) * k3[1] + (2197 / 4104) * k4[1] - (1 / 5) * k5[1];

                val[0] = vec[0];
                val[1] = vec[1];
                val[2] = vec[2];
                val[3] = vec[3];
                Traj.push_back(val);
                flag = 0;
            }
            else
            { // change the value of h here using the formula
                double delta = (0.84) * pow(TOL / maxerror, 1 / 4);
                if (delta <= 0.05) // to ensure a huge or very minimal step change occur
                {
                    h = 0.05 * h;
                }
                else if (h >= 4)
                {
                    h = 4 * h;
                }
                else
                {
                    h = delta * h;
                }
                flag = 1;
            }
        }

        t0 += h;
        flag = 1;
    }

    for (int l = 0; l < Traj.size(); l++)
    {
        for (int j = 0; j < Traj[0].size(); j++)
        {
            cout << Traj[l][j] << setprecision(15) << "\t";
        }
        cout << endl;
    }

    return 0;
}