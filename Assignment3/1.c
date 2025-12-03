#include <stdio.h>
#include <math.h>

double min(double a, double b) {
    return (a < b) ? a : b;
}

double calculateFixedInstallment(double principal, double rate, int years) {
    if (rate == 0) {
        return principal / years;
    }
    return principal * (rate * pow(1 + rate, years)) / (pow(1 + rate, years) - 1);
}

double calculateRepayment(double loan, double interestRate, int years,
                          double installment, double extraPayment,
                          int currentYear, double totalPaid) {
    if (years == 0 || loan <= 0) {
        return totalPaid;
    }

    double interest = loan * interestRate;
    double loanWithInterest = loan + interest;

    double totalDueThisYear = loanWithInterest;
    double payment = min(installment + extraPayment, totalDueThisYear);

    double remainingLoan = loanWithInterest - payment;

    printf("Year %d: Extra Payment = $%.2f, Remaining loan = $%.2f\n",
           currentYear, extraPayment, remainingLoan);

    return calculateRepayment(
        remainingLoan,
        interestRate,
        years - 1,
        installment,
        extraPayment,
        currentYear + 1,
        totalPaid + payment
    );
}

int main() {
    double principal = 100000.0;
    double rate = 0.05;
    int years = 3;

    double installment = calculateFixedInstallment(principal, rate, years);
    double extraPayment = 2000.0;

    printf("Loan Details:\n");
    printf("Principal: $%.2f\n", principal);
    printf("Interest Rate: %.1f%%\n", rate * 100);
    printf("Duration: %d years\n", years);
    printf("Annual Installment: $%.2f\n", installment);
    printf("Extra Yearly Payment: $%.2f\n\n", extraPayment);

    double totalRepayment = calculateRepayment(principal, rate, years, installment, extraPayment, 1, 0.0);

    printf("\nTotal Repayment: $%.2f\n", totalRepayment);
    printf("Total Interest Paid: $%.2f\n", totalRepayment - principal);

    return 0;
}
/*
    ============================================================
EXPLANATION OF THE LOAN REPAYMENT RECURSIVE PROGRAM
============================================================

1. calculateFixedInstallment(principal, rate, years)
   - Uses the annuity formula to compute a fixed yearly installment.
   - Ensures equal payments over the selected number of years.

2. calculateRepayment(...)
   - A recursive function that computes the loan balance year by year.
   - Steps followed each recursive call:
       a) Apply yearly interest to the loan.
       b) Deduct a fixed installment (but never pay more than needed).
       c) Compute remaining loan.
       d) Print remaining loan for that year.
       e) Recurse for the next year.

3. Base Cases:
   - If years == 0 → Stop recursion (all years processed).
   - If loan <= 0 → Loan fully repaid.

4. Recursive Case:
   - Adds interest → subtracts payment → updates loan.
   - Moves to next year by calling calculateRepayment() again.

5. Total repayment:
   - Returned value sums all payments made over recursive calls.

6. Why Recursion Works Well Here:
   - Models loan repayment naturally year-by-year.
   - Each function call represents one year.
   - Tracks the remaining loan cleanly without loops.
   - Keeps the logic simple and clear.

============================================================
*/