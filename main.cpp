#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

ifstream fin("tests.in");
ofstream fout("output.csv");

vector<long long> output, cnt;


// Radix Sort

long long get_max(vector<long long> v){
    long long mx = v[0];
    for (auto i: v)
        if (i > mx)
            mx = i;
    return mx;
}

void count_sort_by_exp(vector<long long> &v, long long n, long long exp, int base){
    output = vector<long long>(n);
    cnt = vector<long long>(base, 0);

    for(auto i: v)
        cnt[(i/exp) % base]++;

    long long i;
    for(i = 1; i < base; i++)
        cnt[i] += cnt[i-1];

    for(i = n-1; i >= 0; i--)
        output[--cnt[(v[i]/exp) % base]] = v[i];

    v = output;
}

void count_sort_by_exp_65536(vector<long long> &v, long long n, long long exp){
    output = vector<long long>(n);
    cnt = vector<long long>(65536, 0);
    long long i;
    for(int i = 0 ; i < n; i++)
        cnt[(v[i]/exp) & 65535]++;


    for(i = 1; i < 65536; i++)
        cnt[i] += cnt[i-1];

    for(i = n-1; i >= 0; i--)
        output[--cnt[(v[i]/exp) & 65535]] = v[i];

    v = output;
}

void radix_sort(vector<long long> &v, long long n, long long base){
    long long mx = get_max(v), exp;
    if (base == 65536) // 2^16
        for (exp = 1; mx/exp > 0; exp *= base)
            count_sort_by_exp_65536(v, n, exp);
    else
        for (exp = 1; mx/exp > 0; exp *= base)
            count_sort_by_exp(v, n, exp, base);
}



// Merge sort

void merge(vector<long long> &v, long long left, long long right, long long mid){
    output = vector<long long>(right - left + 1);
    long long i = left, j = mid + 1, k = 0;

    while(i <= mid && j <= right) {

        if(v[i] <= v[j])
            output[k] = v[i++];
        else
            output[k] = v[j++];
        k++;
    }

    while(i <= mid)
        output[k++] = v[i++];

    while(j <= right)
        output[k++] = v[j++];


    for (i = left, k = 0; i <= right; i++, k++)
        v[i] = output[k];
}

void merge_sort(vector<long long> &v, long long left, long long right){

    if (left < right) {
        long long mid = left + (right - left)/ 2;
        merge_sort(v, left, mid);
        merge_sort(v, mid + 1, right);

        merge(v, left, right, mid);
    }
}


// Shell sort

void shell_sort(vector<long long> &v, long long n){
    long long gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2){

        for (i = gap; i < n; ++i){
            temp = v[i];

            for (j = i; j >= gap && v[j - gap] > temp; j -= gap)
                v[j] = v[j - gap];

            v[j] = temp;
        }
    }
}

void shell_sort_knuth(vector<long long> &v, long long n){
    long long d, i, gap = 1, temp, j;
    while(gap < n)
        gap = gap * 3 + 1;
	d = gap;
	while(d > 0){

		for (i = d; i < n; i += 1){
			temp = v[i];

			for (j = i; j >= d && v[j - d] > temp; j -= d)
				v[j] = v[j - d];
			v[j] = temp;
		}
		d--;
		d /= 3;
	}
}


// Heap sort

void swap_val(vector<long long> &v, long long i, long long j){
    long long aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void heapify(vector<long long> &v, long long n, long long i){
    long long largest = i, left = i * 2 + 1, right = i * 2 + 2;

    if (left < n && v[left] > v[largest])
        largest = left;

    if (right < n && v[right] > v[largest])
        largest = right;

    if (largest != i) {
        swap_val(v, i, largest);
        heapify(v, n, largest);
    }
}

void heap_sort(vector<long long> &v, long long n){
    long long i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (i = n - 1; i > 0; i--) {
        swap_val(v, 0, i);
        heapify(v, i, 0);
    }
}


//Quick sort


long long rand_between(long long a, long long b){
    return a + (rand() % (b - a + 1));
}

long long partition(vector<long long> &v, long long l, long long r){
    long long pivot = v[r];

    long long i = (l - 1), j;

    for (j = l; j <= r - 1; j++){
        if (v[j] <= pivot) {
            i++;
            swap_val(v, i, j);
        }
    }
    swap_val(v, i + 1, r);
    return (i + 1);
}

long long rand_partition(vector<long long> &v, long long l, long long r){
    long long random = rand_between(l, r);
    swap_val(v, random, r);

    return partition(v, l, r);
}

void quick_sort_rand(vector<long long> &v, long long l, long long r){
    if(l>=r) return;
    long long pi = rand_partition(v, l, r);

    quick_sort_rand(v, l, pi - 1);
    quick_sort_rand(v, pi + 1, r);
}


void quick_sort_3(vector<long long> &v, long long left, long long right){
    if (left >= right)
        return;
    long long a, b, c, mid;
    a = rand_between(left, right);
    b = rand_between(left, right);
    c = rand_between(left, right);
    mid = left + (right - left)/ 2;

    if(v[c] < v[a] && v[a] < v[b] || v[b] < v[a] && v[a] < v[c])
        swap_val(v, a, mid);
    else if(v[a] < v[b] && v[b] < v[c] || v[c] < v[b] && v[b] < v[a])
        swap_val(v, b, mid);
    else
        swap_val(v, c, mid);

    long long i = left, j = right, d = 0;
    while(i < j){
        if(v[i] > v[j]){
            swap_val(v, i, j);
            d = 1 - d;
        }
        i += d;
        j -= 1 - d;
    }
    quick_sort_3(v, left, i - 1);
    quick_sort_3(v, i + 1, right);
}



void  generate_rand_vector(vector<long long>& v, long long nr_elem, long long max_val){
    v = vector<long long>(nr_elem);
    mt19937_64 gen(time(NULL));
    uniform_int_distribution<unsigned long long> distr(0, max_val);

    for (long long i = 0; i < nr_elem; i++){
        v[i] = distr(gen);
    }
}

bool test_is_sorted(vector<long long> v, long long n) {
    for(long long i = 1; i < n; i++)
        if (v[i-1] > v[i])
            return false;
    return true;
}

void print(vector<long long> v, long long n){
    for(long long i = 0; i < n; i++)
        cout << v[i] << " ";
    cout <<'\n';
}


int main(){

    vector<long long> v, v_copy;

    long long nr_tests, nr_elem, max_val, i;
    long long mode = 2;
    //cin >> mode;
    if(mode == 1){
        fin >> nr_tests;

        for (i = 0; i < nr_tests; ++i){
            fin >> nr_elem >> max_val;
            if(nr_elem > 1000000000){
                cout << "Sorting algorithms cannot be run, number of elements too big (n = "<<nr_elem<<")\n";
                return 0;
            }
            generate_rand_vector(v, nr_elem, max_val);
            v_copy = v;

            cout << "Test " << i + 25<< " ----------------- N = " << nr_elem << " ---------- MaxVal = " << max_val <<'\n';
            cout << "Algorithm --------------- State ------------ Time (microseconds)\n";

            cout << "Radix sort ------------- ";
            v = v_copy;
            auto start = chrono::high_resolution_clock::now();
            radix_sort(v, nr_elem, 10);
            auto stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, nr_elem)){
                cout << "Success ---------------- ";
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                cout << duration << " ---------------- Base 10\n";

            } else
                cout << "Fail :(\n";

            cout << "Radix sort ------------- ";
            v = v_copy;
            start = chrono::high_resolution_clock::now();
            radix_sort(v, nr_elem, 65536);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, nr_elem)){
                cout << "Success ---------------- ";
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                cout << duration << " ---------------- Base 2^16 \n";

            } else
                cout << "Fail :(\n";

            cout << "Merge sort ------------- ";

            v = v_copy;
            output = vector<long long>(nr_elem);
            start = chrono::high_resolution_clock::now();
            merge_sort(v, 0, nr_elem - 1);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, nr_elem)){
                cout << "Success ---------------- ";
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                cout << duration << "\n";
            } else
                cout << "Fail :(\n";


            cout << "Shell sort ------------- ";

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            shell_sort(v, nr_elem);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, nr_elem)){
                cout << "Success ---------------- ";
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                cout << duration << "\n";
            } else
                cout << "Fail :(\n";

            cout << "Shell sort ------------- ";

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            shell_sort_knuth(v, nr_elem);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, nr_elem)){
                cout << "Success ---------------- ";
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                cout << duration << " ---------------- Knuth\n";
            } else
                cout << "Fail :(\n";

            cout << "Heap sort -------------- ";
            v = v_copy;
            start = chrono::high_resolution_clock::now();
            heap_sort(v, nr_elem);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, nr_elem)){
                cout << "Success ---------------- ";
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                cout << duration << "\n";
            } else
                cout << "Fail :(\n";


            cout << "Quick sort ------------- ";

            v = v_copy;
            if (nr_elem < 100000000){
                start = chrono::high_resolution_clock::now();
                quick_sort_rand(v, 0, nr_elem-1);
                stop = chrono::high_resolution_clock::now();
                if (test_is_sorted(v, nr_elem)){
                    cout << "Success ---------------- ";
                    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                    cout << duration << " ---------------- pivot random element\n";
                } else
                    cout << "Fail :(\n";

                cout <<"Quick sort ------------- ";

                v = v_copy;
                start = chrono::high_resolution_clock::now();
                quick_sort_3(v, 0, nr_elem-1);
                stop = chrono::high_resolution_clock::now();
                if (test_is_sorted(v, nr_elem)){
                    cout << "Success ---------------- ";
                    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                    cout << duration << " ---------------- pivot median of 3\n";
                } else
                    cout << "Fail :(\n";
            } else
                cout <<"Can not perform, number of elements too big\n";



            cout<< "STL sort --------------- Success ---------------- ";
            v = v_copy;
            start = chrono::high_resolution_clock::now();
            sort(v.begin(), v.end());
            stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
            cout << duration << "\n\n\n";
        }
    } else {
        long long l = 10000000, r = 100000000, step = 5000000, val_max =100000000000000; // 10^7 - 10^8, step = 5 * 10^6, 10^14
        //cin >> l >> r >> step >> val_max;
        fout <<",Radix Sort(Base 10), Radix Sort(Base 2^16), Merge Sort, Shell Sort, Shell Sort(Knuth), Heap Sort, Quick Sort(randomized), Quick Sort(median of 3), STL Sort\n";

        for(long long i = l; i <= r; i += step){
            fout << i;
            generate_rand_vector(v, i, val_max);
            v_copy = v;

            auto start = chrono::high_resolution_clock::now();
            radix_sort(v, i, 10);
            auto stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<","<<-1;

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            radix_sort(v, i, 65536);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<","<<-1;


            v = v_copy;
            output = vector<long long>(i);
            start = chrono::high_resolution_clock::now();
            merge_sort(v, 0, i - 1);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<","<<-1;

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            shell_sort(v, i);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<","<<-1;

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            shell_sort_knuth(v, i);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<"," << -1;

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            heap_sort(v, i);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<"," << -1;

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            quick_sort_rand(v, 0, i-1);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<"," << -1;

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            quick_sort_3(v, 0, i-1);
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<"," << -1;

            v = v_copy;
            start = chrono::high_resolution_clock::now();
            sort(v.begin(), v.end());
            stop = chrono::high_resolution_clock::now();
            if (test_is_sorted(v, i)){
                auto duration = chrono::duration_cast<chrono::microseconds>(stop-start).count();
                fout << "," << duration;
            } else
                fout <<"," << -1;
            fout<<"\n";
        }

    }
    fout.close();

    return 0;
}
