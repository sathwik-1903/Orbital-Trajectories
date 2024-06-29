#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9 + 7;
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

void generateDE(vector<double> &y, vector<double> &dydt)
{
    double x = y[0];
    double y_val = y[1];
    double vx = y[2];
    double vy = y[3];

    // equations
    dydt[0] = vx;           // dx/dt= vx
    dydt[1] = vy;           // dydt= vy
    dydt[2] = f1(x, y_val); // dvx/dt= f1(x,y)
    dydt[3] = f2(x, y_val); // dvy/dt= f2(x,y)
}
vector<double> rk4(double t, vector<double> &y, double &h, double epsilon)
{
    vector<double> y_temp = y;
    vector<double> k1(4), k2(4), k3(4), k4(4), k5(4), k6(4);
    // k1
    generateDE(y, k1);

    // k2
    for (int i = 0; i < 4; i++)
    {
        y_temp[i] = y[i] + 0.5 * h * k1[i];
    }
    generateDE(y_temp, k2);

    // k3
    for (int i = 0; i < 4; i++)
    {
        y_temp[i] = y[i] + 0.5 * h * k2[i];
    }
    generateDE(y_temp, k3);

    // k4
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] + 1 * h * k3[i];
    }
    generateDE(y_temp, k4);

    vector<double> y_new(4);
    for (int i = 0; i < 4; i++)
    {
        y_new[i] = y[i] + (1 / 6) * h * k1[i] + (1 / 3) * h * k2[i] + (1 / 3) * h * k3[i] + (1 / 6) * h * k4[i];
    }
    y = y_new;
    vector<double> pr = y_new;

    for (int i = 0; i < 4; i++)
    {
        cout << y_new[i] << " ";
    }

    return pr;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<double> y(4); // initial value input
    double TOL = 1e-2;
    double a, b;
    double h = 0.1; // step size
    double t = 0.0; // time

    vector<vector<double>> Traj;
    vector<double> Stepsize;
    vector<double> error_vector;

    cin >> y[0] >> y[1] >> y[2] >> y[3] >> a >> b;

    // while (t < b)
    // {
    //     vector<double> val = rk4(t, y, h, TOL);
    //     val = rk4(t, y, h, TOL);
    //     Traj.push_back(val);

    //     t += h;
    //     cout << endl;
    // }

    vector<double>val2 = rk4(t,y,h,TOL);
    for (int i = 0; i < 4; i++)
    {
        cout<<val2[i]<<" ";
    }
    

    // all the outputs
    // for (int i = 0; i < Traj.size(); i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         cout << setprecision(15);
    //         cout << Traj[i][j] << "  ";
    //     }
    //     cout << endl;
    // }
    return 0;
}