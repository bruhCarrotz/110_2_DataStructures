#include <iostream>
#include <bits/stdc++.h>
#include "function.h"
using namespace std;

template <class T>
void merge(T *arr, int l, int mid, int r){
    int size1 = mid - l + 1;
    int size2 = r - mid;

    T left[size1], right[size2];

    for (int i = 0; i < size1; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < size2; j++)
        right[j] = arr[mid + 1 + j];

    int i=0, j=0, k=l;
    while (i < size1 && j < size2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } 
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < size1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < size2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

template <class T>
void mySort(T arr[], int l, int r){
    if(l < r) {
        int middle = l+(r-l)/2;
        mySort(arr, l, middle);
        mySort(arr, middle+1, r);
        merge(arr, l, middle, r);
    }
}

void traffic_at(pair< pair<int,int>, int > pair_arr[], int time, int size){
    //first.first = arrival ; first.second = depart ; second = ppl
    unsigned long long int value = 0;
    for(int i=0 ; i<size ; i++){
        for(int j=pair_arr[i].first.first ; j<pair_arr[i].first.second ; j++){
            if(j == time){
                value += pair_arr[i].second;
            }
        }
    } 
    cout << value << endl;
}

void max_traffic(pair< pair<int,int>, int > pair_arr[], int size){
    //first.first = arrival ; first.second = depart ; second = ppl
    int earliest = pair_arr[0].first.first;
    int latest = pair_arr[size-1].first.second;
    
    unsigned long long maxi = 0;
    int max_time;

    for(int i=earliest ; i<=latest ; i++){
        unsigned long long int tmp = 0;
        for(int j=0 ; j<size ; j++){
            if(pair_arr[j].first.second > i && pair_arr[j].first.first <= i){
                tmp += pair_arr[j].second;
            }
        }
        if(tmp > maxi){
            maxi = tmp;
            max_time = i;
        }
    }
    cout << max_time << " " << maxi << endl;
}

void store_list(string *places, int size){
    string temp[size];
    int i, j, k = 0;
    for (i = 0; i < size; i++){
        for (j = 0; j < k; j++){
            if (places[i] == temp[j])
                break;
        }
        if (j == k){
            temp[k] = places[i];
            k++;
        }
    }
    mySort(temp, 0, k-1);
    for(int i=0; i<k; i++){
        if(i != k-1) cout << temp[i] << " ";
        else cout << temp[i] << endl;
    }
}

void solve(){
    int n;
    cin >> n;

    pair< pair<int,int> , int > pair_arr[n];
    int people, arrival, depart;
    string places[n], store;
    
    for (int i=0 ; i<n ; i++) {
        cin >> people;
        pair_arr[i].second = people;

        cin >> arrival;
        pair_arr[i].first.first = arrival;

        cin >> depart;
        pair_arr[i].first.second = depart;

        cin >> store;
        places[i] = store;
    }

    mySort(pair_arr, 0, n-1);

    int num_queries;
    cin >> num_queries;
    for(int i=0 ; i<num_queries ; i++){
        string command;
        cin >> command;
        if(command == "TIME_ARRIVE"){
            int k;
            cin >> k;
            cout << pair_arr[k-1].first.first << endl;
        }
        else if(command == "TRAFFIC_AT"){
            int time;
            cin >> time;
            traffic_at(pair_arr, time, n);
        }
        else if(command == "MAX_TRAFFIC"){ 
            max_traffic(pair_arr, n);
        }
        else if(command == "STORE_LIST"){
            store_list(places, n);
        }
    }
}