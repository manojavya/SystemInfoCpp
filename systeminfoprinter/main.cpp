#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <memory>
#include <array>

using namespace std;

int main(){
    time_t timestamp;
    time(&timestamp);
    ofstream fileOut("out.txt");
    if (fileOut.is_open()){
        fileOut << "v0.0.1 | Test release, BETA \n";
        fileOut << "Log " << ctime(&timestamp) << "\n";
        fileOut << "Successfully Started at " << ctime(&timestamp) << "\n";
        fileOut << "Will be using pkexec to get root level details \n"; 
    }

    //dmesg
    FILE* pipe = popen("pkexec dmesg", "r");
    cout << pipe << "\n";
    char buffer[256];
    cout << "=== dmesg output ===\n";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr){
        cout << buffer;
        fileOut << buffer;
    }
    int status = pclose(pipe);
    if (status != 0){
        cerr << "dmesg command failed with status: " << status << "\n";
        fileOut << "dmesg failed with status: " << status << "\n";
    } else {
        fileOut << "dmesg ran successfully at " << ctime(&timestamp) << "\n";
    }

    //hostnamectl
    pipe = popen("hostnamectl", "r");
    cout << pipe << "\n";
    cout << "=== hostnamectl output ===\n";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr){
        cout << buffer;
        fileOut << buffer;
    }
    status = pclose(pipe);
    if (status != 0){
        cerr << "hostnamectl command failed with status: " << status << "\n";
        fileOut << "hostnamectl failed with status: " << status << "\n";
    } else {
        fileOut << "hostnamectl ran successfully at " << ctime(&timestamp) << "\n";
    }

    //lsblk
    pipe = popen("lsblk", "r");
    cout << pipe << "\n";
    cout << "=== lsblk output ===\n";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr){
        cout << buffer;
        fileOut << buffer;
    }
    status = pclose(pipe);
    if (status != 0){
        cerr << "lsblk command failed with status: " << status << "\n";
        fileOut << "lsblk failed with status: " << status << "\n";
    } else {
        fileOut << "lsblk ran successfully at " << ctime(&timestamp) << "\n";
    }

    //lscpu
    pipe = popen("lscpu", "r");
    cout << pipe << "\n";
    cout << "=== lscpu output ===\n";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr){
        cout << buffer;
        fileOut << buffer;
    }
    status = pclose(pipe);
    if (status != 0){
        cerr << "lscpu command failed with status: " << status << "\n";
        fileOut << "lscpu failed with status: " << status << "\n";
    } else {
        fileOut << "lscpu ran successfully at " << ctime(&timestamp) << "\n";
    }

    cout << "Program Executed please check the out.txt for full information\n";
    fileOut.close();
    return(0);
}