#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <config.h>


using u32 = unsigned int;


std::string usage = "\n"
"Usage: \n"
"   duiduipeng [-h --help] : show this help\n"
"              [-n val] : buy val balls ( >= 1)\n"
"              [-t] : enter test mode. Without this flag, it will simulate with number of balls you give with '-n' flag\n"
"              [-tn val] : update NUM_TEST_PER_NUMBER to val ( >= 10)\n";


std::mutex mtx;
u32 LUCKY_NUM = 3;
u32 NUM_TEST_PER_NUMBER = 10000;
u32 NUM_GET_FOR_3 = 3;
u32 NUM_GET_FOR_DOUBLE = 1;
u32 NUM_GET_FOR_ALL_DIFFERENT = 5;
u32 NUM_GET_FOR_ALL_CLEAN = 5;
u32 NUM_OF_COLOR = 10;
#define BUY_NUM_MAXIMUM 40
float Prices[BUY_NUM_MAXIMUM] = {
    1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f,
    11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f, 19.f, 20.f,
    21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f,
    31.f, 32.f, 33.f, 34.f, 35.f, 36.f, 37.f, 38.f, 39.f, 40.f
};



std::random_device rd;                        // Seed for random generator
std::mt19937 gen(rd());                       // Mersenne Twister generator
std::uniform_int_distribution<> distr(1, NUM_OF_COLOR); 


void reset_list(u32* list){
    memset(list, 0, 9*sizeof(u32));
}


void fill_list(u32* list, u32& num_current, u32& num_get){
    u32 index = 0;
    while (index < 9 && num_current >= 1){
        if (list[index] == 0) {
            u32 random_ball = distr(gen);
            if (random_ball == LUCKY_NUM){
                num_current ++;
                num_get ++;
            }
            list[index] = random_ball;
            num_current --;
        }
        index ++;
    }
}


void check_3_1_link(u32& num_get, u32& num_current, u32* list){
    /*
        check 3 balls with linked number
    */
    u32 index = 0;
    while (index < 6){
        if ( list[index]!= 0 && list[index] == list[index+1] && list[index] == list[index+2]){
            list[index] = list[index+1] = list[index+2] = 0; // set them to 0
            num_get += NUM_GET_FOR_3; 
            num_current += NUM_GET_FOR_3;
            index += 3;
        }
        else {
            index ++;
        }
    }
}


void check_3_2_colunm(u32& num_get, u32& num_current, u32* list){
    /*
        check 3 balls with same number in the same column
    */
    u32 index = 0;
    while (index < 3){
        if (list[index] != 0 && list[index] == list[index+3] && list[index] == list[index+6]){
            list[index] = list[index+3] = list[index+6] = 0;
            num_get += NUM_GET_FOR_3;
            num_current += NUM_GET_FOR_3;
            index ++;
        }
        else {
            index ++;
        }
    }
}


void check_3_3_diagonal(u32& num_get, u32& num_current, u32* list){
    /*
        check 3 balls with same number in the diagonal
    */
    if (list[0] != 0 && list[0] == list[4] && list[0] == list[8]){
        list[0] = list[4] = list[8] = 0;
        num_get += NUM_GET_FOR_3;
        num_current += NUM_GET_FOR_3;
    }
    if (list[2] != 0 && list[2] == list[4] && list[2] == list[6]){
        list[2] = list[4] = list[6] = 0;
        num_get += NUM_GET_FOR_3;
        num_current += NUM_GET_FOR_3;
    }
}


void check_3(u32& num_get, u32& num_current, u32* list){
    check_3_1_link(num_get, num_current, list);
    check_3_2_colunm(num_get, num_current, list);
    check_3_3_diagonal(num_get, num_current, list);
}


void check_double(u32& num_get, u32& num_current, u32* list){
    for (int i = 0; i < 8; i++){
       for (int j = i+1; j < 9; j++){
           if (list[i] != 0 && list[i] == list[j]){
               list[i] = list[j] = 0;
               num_get += NUM_GET_FOR_DOUBLE;
               num_current += NUM_GET_FOR_DOUBLE;
           }
       }
    }
}


bool check_all_different(u32& num_get, u32& num_current, u32* list){
    std::unordered_set<u32> set;
    bool all_different = true;
    for (int i = 0; i < 9; i++){
        if ( list[i] == 0 || set.count(list[i]) != 0){
            all_different = false;
            break;
        }
    }
    if (all_different){
        num_get += NUM_GET_FOR_ALL_DIFFERENT;
        num_current += NUM_GET_FOR_ALL_DIFFERENT;
        reset_list(list);
    }
    return all_different;
}


void check_all_clean(u32& num_get, u32& num_current, u32* list){
    bool all_clean = true;
    for (int i = 0; i < 9; i++){
        if (list[i] != 0){
            all_clean = false;
            break;
        }
    }
    if (all_clean){
        num_get += NUM_GET_FOR_ALL_CLEAN;
        num_current += NUM_GET_FOR_ALL_CLEAN;
        reset_list(list);
    }
}


u32 run_game(u32 num_buy, bool test_mode = false){
    u32 num_get = num_buy;
    u32 num_current = num_buy;
    if (num_buy == 0) return 0;
    u32* list = new u32[9];
    reset_list(list);
    while (num_current > 0){
        fill_list(list, num_current, num_get);
        check_3(num_get, num_current, list);
        check_double(num_get, num_current, list);
        if (check_all_different(num_get, num_current, list)){
            continue;
        }
        check_all_clean(num_get, num_current, list);
    }
    if (!test_mode) {
        printf("Buy %d balls\n", num_buy);
        printf("Get %d balls\n", num_get);
    }
    delete[] list;
    return num_get;
}


void run_test_game_thread(u32 num_buy, u32 num_works, float& total){
    float local_total = 0.f;
    for (u32 i = 0; i < num_works; i++){
        local_total +=  (float) run_game(num_buy, true);
    }
    std::lock_guard<std::mutex> lock(mtx);
    total += local_total;
}


void run_test_single_game(const u32& num_buy, bool verbose = false){
    if (verbose){
        printf("Buy %d balls\n", num_buy);
        printf("NUM_TEST_PER_NUMBER: %d\n", NUM_TEST_PER_NUMBER);
    }
    u32 num_cpu = std::thread::hardware_concurrency();
    u32 num_works_per_thread = NUM_TEST_PER_NUMBER / num_cpu;
    float total = 0.f;
    std::vector<std::thread> threads;
    for (u32 i = 0; i < num_cpu; i++){
        threads.emplace_back(run_test_game_thread, num_buy, num_works_per_thread, std::ref(total));
    }
    for (auto& t: threads){
        if (t.joinable()) t.join();
    }
    float average_num = total / (float) NUM_TEST_PER_NUMBER;
    printf(
        "Buy %d, average ratio: %f, prices_per_ball: %f\n", 
        num_buy,  
        average_num / (float) num_buy, 
        (num_buy > BUY_NUM_MAXIMUM ? num_buy * 1.0 : Prices[num_buy-1]) / average_num);
}


void run_test_summary(){
    fprintf(stdout, "=============\n");
    fprintf(stdout, "Test mode\n");
    fprintf(stdout, "Test every number test for %d times\n", NUM_TEST_PER_NUMBER);
    for ( u32 num_buy_tmp = 1; num_buy_tmp < BUY_NUM_MAXIMUM + 1; num_buy_tmp++){
        run_test_single_game(num_buy_tmp);
    }
}


void show_usage(){
    fprintf(stderr, "%s\n", usage.c_str());
}


void show_version(){
    fprintf(stdout, "===================\n");
    fprintf(stdout, "DuiDuiPeng Version: %d.%d.%d\n\n", duiduipeng_VERSION_MAJOR, duiduipeng_VERSION_MINOR, duiduipeng_VERSION_PATCH);
}


int main(int argc, char* argv[]){

    show_version();

    int index = 0;
    bool test_mode = false;
    u32 num_buy = 0;
    while (index < argc){
        if (std::string(argv[index]) == "-n") {
            if (argv[index+1] == NULL) {
                fprintf(stderr, "Please input the number for '-n' NUM_BUY (>10)\n");
                show_usage();
                exit(1);
            }
            num_buy = (u32)(std::stoi(argv[++index]));
            if (num_buy <= 0){
                fprintf(stderr, "Please input the valid number for '-n' NUM_BUY (>10)\n");
                show_usage();
                exit(1);
            }
        }
        else if (std::string(argv[index]) == "-t"){
            test_mode = true;
        }
        else if (std::string(argv[index]) == "-tn"){
            if (argv[index+1] == NULL) {
                fprintf(stderr, "Please input the number for '-tn' NUM_TEST_PER_NUMBER\n");
                show_usage();
                exit(1);
            }
            u32 tn = (u32)(std::stoi(argv[++index]));
            if (tn < 10) {
                fprintf(stderr, "NUM_TEST_PER_NUMBER should be at least 10\n");
                show_usage();
                exit(1);
            }
            NUM_TEST_PER_NUMBER = tn;
            fprintf(stdout, "Update NUM_TEST_PER_NUMBER: %d\n", NUM_TEST_PER_NUMBER);
        }
        else if (std::string(argv[index]) == "-h" || std::string(argv[index]) == "--help"){
            show_usage();
            exit(0);
        }
        else {
            if (index==0) {
                index ++;
                continue;
            }
            fprintf(stdout, "Warning: invalid input: %s\n", argv[index]);
        }

        index ++;
    }

    // run the game or into test mode
    if (!test_mode){
        fprintf(stdout, "=============\n");
        fprintf(stdout, "Simu-mode\n");
        if (num_buy == 0){
            fprintf(stderr, "No number inputted\n");
            show_usage();
            exit(1);
        }
        run_test_single_game(num_buy, true);
        return 0;
    } else {
        run_test_summary();
        return 0;
    }
    
}
