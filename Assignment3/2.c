#include <math.h>
#include <stdio.h>
// Consumes at each planet, Solar Bonus when passing through certain gravitational zones(assuming it to be every third planet),
// Solar recharge every forth.

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    // Base case 1: Fuel exhausted
    if (fuel <= 0) {
        printf("Fuel exhausted.");
        return;
    }
    // Base case 2: All planets visited
    if (planet > totalPlanets) {
        printf("All planets visited.");
        return;
    }
    // Consume fuel
    fuel -= consumption;
    // Gravitational bonus every-assumption-3rd planet
    if ((planet % 3) == 0) {
          fuel += solarBonus;
    }
    // Solar recharge every 4th planet
    if ((planet %4)==0) {
        fuel += recharge;
    }
    // Current status
    printf("Planet%d: Fuel Remaining = %d\n",planet,fuel);
    // Enough fuel to reach the next planet or not
    if (fuel<consumption) {
        printf("Can not reach next planet"); // Can return and end here but we still call again to match the first base case.
    }
    // Recursive call
    calculateFuel(fuel,consumption,recharge,solarBonus,planet+1,totalPlanets);


}
int main() {


}
