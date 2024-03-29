#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip> //fixed << setprecision(10)

#include <sstream> // std::stringstream
#include <bitset>  // std::bitset<N>
#include <stdlib.h>
#include <ctime>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;

#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)

typedef long long ll;
typedef vector<int> vi;

ll id2time(ll id){
    ll message_id = id;
    //cin >> message_id; //ex)175928847299117063

    stringstream ss;
    ss << bitset<64>(message_id);
    string message_id_bin = ss.str();
    //cout << message_id_bin << endl;

    char timestamp_bin[42];
    for(int i = 0; i < 42; i++){
        timestamp_bin[i] = message_id_bin[i];
    }
    //cout << timestamp_bin << endl;
    
    long timestamp = strtol(timestamp_bin, NULL, 2);
    //cout << timestamp << endl;

    ll timestamp_ms = ll(timestamp + 1420070400000);
    //cout << timestamp_ms << endl;

    int unix_timestamp_ms = timestamp_ms % 1000;
    time_t unix_timestamp = timestamp_ms / 1000;
    tm *tm_unix = gmtime(&unix_timestamp);
	// cout << asctime(tm_unix);
    cout << "min: " << tm_unix->tm_min << " ";
    cout << "sec: " << tm_unix->tm_sec << " ";
    cout << "ms: " << unix_timestamp_ms % 1000 << endl;

    return tm_unix->tm_min*100000 + tm_unix->tm_sec*1000 + unix_timestamp_ms % 1000;
}

namespace py = pybind11;
PYBIND11_PLUGIN(getTimeByMessageId) {
    py::module m("getTimeByMessageId", "by pybind11");
    m.def("id2time", &id2time);

    return m.ptr();
}