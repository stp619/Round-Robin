#include <iostream>
#include <climits>
using namespace std;

struct Process {
    int ArrivalTime, BurstTime, StartTime[20], WaitTime, FinishTime, TurnaroundTime;
    char ProcessID;
};

int quantum = 1;

int main() {
    int num_processes, i, j;

    // Taking Input
    cout << "Enter the no. of processes: ";
    cin >> num_processes;
    Process processes[num_processes];

    cout << "Enter the process IDs: " << endl;
    for (i = 0; i < num_processes; i++)
        cin >> processes[i].ProcessID;

    cout << "Enter the Arrival time of processes: " << endl;
    for (i = 0; i < num_processes; i++)
        cin >> processes[i].ArrivalTime;

    cout << "Enter the Burst time of processes: " << endl;
    for (i = 0; i < num_processes; i++)
        cin >> processes[i].BurstTime;

    // Declaring variables
    int remaining_processes = num_processes, s[num_processes][20];
    float current_time = 0, min_value = INT_MAX, b[num_processes], a[num_processes];

    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < num_processes; i++) {
        b[i] = processes[i].BurstTime;
        a[i] = processes[i].ArrivalTime;
        for (j = 0; j < 20; j++) {
            s[i][j] = -1;
        }
    }

    int total_wait_time = 0, total_turnaround_time = 0;
    bool flag = false;

    while (remaining_processes != 0) {
        min_value = INT_MAX;
        flag = false;

        for (i = 0; i < num_processes; i++) {
            float temp_time = current_time + 0.1;
            if (a[i] <= temp_time && min_value > a[i] && b[i] > 0) {
                index = i;
                min_value = a[i];
                flag = true;
            }
        }

        // if at =1 then loop gets out hence set flag to false
        if (!flag) {
            current_time++;
            continue;
        }

        // calculating start time
        j = 0;

        while (s[index][j] != -1) {
            j++;
        }

        if (s[index][j] == -1) {
            s[index][j] = current_time;
            processes[index].StartTime[j] = current_time;
        }

        if (b[index] <= quantum) {
            current_time += b[index];
            b[index] = 0;
        } else {
            current_time += quantum;
            b[index] -= quantum;
        }

        if (b[index] > 0) {
            a[index] = current_time + 0.1;
        }

        // calculating arrival, burst, final times
        if (b[index] == 0) {
            remaining_processes--;
            processes[index].FinishTime = current_time;
            processes[index].WaitTime = processes[index].FinishTime - processes[index].ArrivalTime - processes[index].BurstTime;
            total_wait_time += processes[index].WaitTime;
            processes[index].TurnaroundTime = processes[index].BurstTime + processes[index].WaitTime;
            total_turnaround_time += processes[index].TurnaroundTime;
        }
    } // end of while loop

    // Printing output
    cout << "\tProcess ID ";
    cout << "\tArrival time ";
    cout << "\tBurst time ";
    cout << "\tStart time";
    j = 0;
    while (j != 10) {
        j += 1;
        cout << " ";
    }
    cout << "\t\tFinish time";
    cout << "\tWait Time ";
    cout << "\tTurnaround Time" << endl;

    for (i = 0; i < num_processes; i++) {
        cout<< "\t\t" << processes[i].ProcessID << "\t\t";
        cout << processes[i].ArrivalTime << "\t\t";
        cout << processes[i].BurstTime << "\t";
        j = 0;
        int v = 0;
        while (s[i][j] != -1) {
            cout << processes[i].StartTime[j] << " ";
            j++;
            v += 3;
        }
        while (v != 40) {
            cout << " ";
            v += 1;
        }
        cout << processes[i].FinishTime << "\t\t";
        cout << processes[i].WaitTime << "\t\t";
        cout << processes[i].TurnaroundTime << endl;
    }

    // Calculating average wait time and turnaround time
    double avg_wait_time, avg_turnaround_time;
    avg_wait_time = total_wait_time / static_cast<double>(num_processes);
    avg_turnaround_time = total_turnaround_time / static_cast<double>(num_processes);

    // Printing average wait time and turnaround time
    cout << "The average wait time is: " << avg_wait_time << endl;
    cout << "The average Turnaround time is: " << avg_turnaround_time << endl;

    return 0;
}
