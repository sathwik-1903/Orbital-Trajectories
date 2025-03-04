
#include <bits/stdc++.h>
using namespace std;
double GMs = (1.32712440018) * 1e20;
double GMe = (3.986004418) * 1e14;
// the function needs to be multiplied by GMm
// add the planetary mass
// time based while loop needed instead of for loop
// also makse use of eccentricity in case of inputs

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

int main()
{
    double dt, t0, x0, y0, vx0, vy0;
    cin >> dt >> t0 >> x0 >> y0 >> vx0 >> vy0;
    double x, y;
    vector<double> vec(4);
    int n = 10;
    vec[0] = x0;  // x
    vec[1] = y0;  // y
    vec[2] = vx0; // vx
    vec[3] = vy0; // vy
    int tmax = 10;
    vector<vector<double>> Traj;
    int i = 0;
    vector<double> k1(4), k2(4), k3(4), k4(4);
    while (t0 <= tmax)
    {
        vector<double> val(4);
        x = vec[0]; // initial val of x
        y = vec[1]; // initial val of y
        // vec[0] = x + dt * vec[2];//updated to the nxt of x
        // vec[1] = y + dt * vec[3];//updated to the nxt of y

        double k1 = dt * f1(x, y);
        double k2 = dt * f1(x + k1 / 2, y + k1 / 2);
        double k3 = dt * f1(x + k2 / 2, y + k2 / 2);
        double k4 = dt * f1(x + k3, y + k3);
        double k = k1 / 6 + k2 / 3 + k3 / 3 + k4 / 6;
        vec[2] += k;

        k1 = dt * f2(x, y);
        k2 = dt * f2(x + k1 / 2, y + k1 / 2);
        k3 = dt * f2(x + k2 / 2, y + k2 / 2);
        k4 = dt * f2(x + k3, y + k3);
        k = k1 / 6 + k2 / 3 + k3 / 3 + k4 / 6;
        vec[3] += k;

        val[0] = vec[0];
        val[1] = vec[1];
        val[2] = vec[2];
        val[3] = vec[3];

        t0 += dt;
        Traj.push_back(val);
        // cout<<Traj[i][1]<<endl;
        // cout<<Traj[i][0]<<"\t"<< Traj[i][1]<<" \t"<<Traj[i][2]<<"\t "<< Traj[i][3];
        // cout <<endl;
        // i++;
    }
    for (int l = 0; l < Traj.size(); l++)
    {
        for (int j = 0; j < Traj[0].size(); j++)
        {
            cout << Traj[l][j] << setprecision(15) << " ";
        }
        cout << endl;
    }
}