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

void generateDE(double t, vector<double> &y, vector<double> &dydt)
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

// one iteration of rk45 without adaptive step
pair<vector<double>, double> rk45(double t, vector<double> &y, double &h, double epsilon)
{
    vector<double> y_temp = y;
    vector<double> k1(4), k2(4), k3(4), k4(4), k5(4), k6(4);
    // k1
    generateDE(t, y, k1);

    // k2
    for (int i = 0; i < 4; i++)
    {
        y_temp[i] = y[i] + 0.25 * h * k1[i];
    }
    generateDE(t + 0.25 * h, y_temp, k2);

    // k3
    for (int i = 0; i < 4; i++)
    {
        y_temp[i] = y[i] + 3.0 / 32.0 * h * k1[i] + 9.0 / 32.0 * h * k2[i];
    }
    generateDE(t + 3.0 / 8.0 * h, y_temp, k3);

    // k4
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] + 1932.0 / 2197.0 * h * k1[i] - 7200.0 / 2197.0 * h * k2[i] + 7296.0 / 2197.0 * h * k3[i];
    }
    generateDE(t + 12.0 / 13.0 * h, y_temp, k4);

    // k5
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] + 439.0 / 216.0 * h * k1[i] - 8.0 * h * k2[i] + 3680.0 / 513.0 * h * k3[i] - 845.0 / 4104.0 * h * k4[i];
    }
    generateDE(t + h, y_temp, k5);

    // k6
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] - 8.0 / 27.0 * h * k1[i] + 2.0 * h * k2[i] - 3544.0 / 2565.0 * h * k3[i] + 1859.0 / 4104.0 * h * k4[i] - 11.0 / 40.0 * h * k5[i];
    }
    generateDE(t + 0.5 * h, y_temp, k6);
    // these dont have h multiplied

    // errors
    vector<double> error(4), y_new(4);

    for (int i = 0; i < 4; i++)
    {
        y_new[i] = y[i] + (25.0 / 216.0) * h * k1[i] + (1408.0 / 2565.0) * h * k3[i] + (2197.0 / 4104.0) * h * k4[i] - h * k5[i] * (1 / 5.0);
        error[i] = fabs(h * ((1.0 / 360.0) * k1[i] - (128.0 / 4275.0) * k3[i] - (2197.0 / 75240.0) * k4[i] + (1.0 / 50.0) * k5[i] + (2.0 / 55.0) * k6[i]));
    }

    double max_error = error[0];
    for (int i = 0; i < 4; i++)
    {
        max_error = max(max_error, error[i]);
    }

    y = y_new;

    pair<vector<double>, double> pr = make_pair(y, max_error);
    return pr;

    // //  Update the solution vector
}
// y is the vector where we initialise functions

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

    while (t < b)
    {
        vector<double> val = rk45(t, y, h, TOL).first;
        double maxError = rk45(t, y, h, TOL).second;
        error_vector.push_back(maxError);

        if (maxError > TOL) // repeat the loop
        {
            h *= 0.84 * pow(TOL / maxError, 0.25);
            vector<double> val = rk45(t, y, h, TOL).first; // the updated value of h here
            Stepsize.push_back(h);
        }
        else
        {
            val = rk45(t, y, h, TOL).first;
            Traj.push_back(val);
            Stepsize.push_back(h);
        }
        t += h;
    }

    // all the outputs
    for (int i = 0; i < Traj.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << setprecision(15);
            cout << Traj[i][j] << "  ";
        }
        cout << endl;
    }

    // output for stepsize
    // for (int i = 0; i < Stepsize.size(); i++)
    // {
    //     cout << Stepsize[i] << endl;
    // }

    // for error outputs
    // for (int i = 0; i < error_vector.size(); i++)
    // {
    //     cout << error_vector[i] << endl;
    // }

    return 0;
}