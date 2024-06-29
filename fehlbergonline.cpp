#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm> // for std::max_element

using namespace std;

double f1(double x, double y)
{
    return -x * y; 
}

double f2(double x, double y)
{
    return x * y - y - x; 
}


// Define your system of equations
void ode_func(double t, const vector<double> &y, vector<double> &dydt)
{
    // Extract variables
    double x = y[0];
    double y_val = y[1];
    double vx = y[2];
    double vy = y[3];

    // Equations
    dydt[0] = vx;           // dx/dt = vx
    dydt[1] = vy;           // dy/dt = vy
    dydt[2] = f1(x, y_val); // dvx/dt = f1(x, y)
    dydt[3] = f2(x, y_val); // dvy/dt = f2(x, y)
}


void rk45_step(double t, vector<double> &y, double &h, double epsilon)
{
    // Temporary storage for intermediate values
    vector<double> y_temp = y;
    vector<double> k1(4), k2(4), k3(4), k4(4), k5(4), k6(4), dydt(4);

    // Step 1: Compute k1
    ode_func(t, y, k1);

    // Step 2: Compute k2
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] + 0.25 * h * k1[i];
    }
    ode_func(t + 0.25 * h, y_temp, k2);

    // Step 3: Compute k3
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] + 3.0 / 32.0 * h * k1[i] + 9.0 / 32.0 * h * k2[i];
    }
    ode_func(t + 3.0 / 8.0 * h, y_temp, k3);

    // Step 4: Compute k4
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] + 1932.0 / 2197.0 * h * k1[i] - 7200.0 / 2197.0 * h * k2[i] + 7296.0 / 2197.0 * h * k3[i];
    }
    ode_func(t + 12.0 / 13.0 * h, y_temp, k4);

    // Step 5: Compute k5
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] + 439.0 / 216.0 * h * k1[i] - 8.0 * h * k2[i] + 3680.0 / 513.0 * h * k3[i] - 845.0 / 4104.0 * h * k4[i];
    }
    ode_func(t + h, y_temp, k5);

    // Step 6: Compute k6
    for (int i = 0; i < 4; ++i)
    {
        y_temp[i] = y[i] - 8.0 / 27.0 * h * k1[i] + 2.0 * h * k2[i] - 3544.0 / 2565.0 * h * k3[i] + 1859.0 / 4104.0 * h * k4[i] - 11.0 / 40.0 * h * k5[i];
    }
    ode_func(t + 0.5 * h, y_temp, k6);

    // Step 7: Compute the solution at t + h and the error estimate
    vector<double> y_new(4), error(4);
    for (int i = 0; i < 4; ++i)
    {
        y_new[i] = y[i] + 25.0 / 216.0 * h * k1[i] + 1408.0 / 2565.0 * h * k3[i] + 2197.0 / 4104.0 * h * k4[i] - h * k5[i] / 5.0;
        error[i] = fabs(h * (1.0 / 360.0 * k1[i] - 128.0 / 4275.0 * k3[i] - 2197.0 / 75240.0 * k4[i] + h / 50.0 * k5[i] + 2.0 / 55.0 * k6[i]));
    }

    // Step 8: Adjust step size based on error estimate
    double max_error = *max_element(error.begin(), error.end());
    if (max_error > epsilon)
    {
        h *= 0.9 * pow(epsilon / max_error, 0.2); // Reduce step size
    }
    else
    {
        h *= 0.9 * pow(epsilon / max_error, 0.25); // Increase step size
    }

    // Step 9: Update the solution vector
    y = y_new;
}

// Main function to perform integration
int main()
{
    // Define initial conditions and integration parameters
    double t = 0.0;
    vector<double> y = {0.0, 0.0, 1.0, 1.0}; // Initial conditions: {x0, y0, vx0, vy0}
    double t_final = 1.0;                    // Final time
    double epsilon = 1e-6;                   // Error tolerance
    double h = 0.1;                          // Initial step size

    // Perform integration
    while (t < t_final)
    {
        // if (t + h > t_final)
        // {
        //     h = t_final - t; // Adjust step size for the last step
        // }
        rk45_step(t, y, h, epsilon);
        t += h;
        // Output the solution at each step if needed
        cout<<y[0]<<" "<<y[1]<<endl;
    }

    // Output the final solution
    cout << "Final solution: ";
    for (double yi : y)
    {
        cout << yi << " ";
    }
    cout << endl;

    return 0;
}
