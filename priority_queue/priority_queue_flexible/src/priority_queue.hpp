// #include <type_traits>

// NOTES: 1. use 2020.2 
// 2. Use constructor to partition member array / include pragma 
//    ERROR: [v++ 214-122] '#pragma HLS' is only allowed in function scope: /mnt/scratch/wenqi/FPGA-ANNS/building_blocks/class_priority_queue/src/priority_queue.hpp:23
enum Order { Collect_smallest, Collect_largest };
// enum class Order { Collect_smallest, Collect_largest };

template<typename T, const int queue_size, Order order> 
class Priority_queue;

template<typename T, const int queue_size> 
class Priority_queue<T, queue_size, Collect_smallest> {
// class Priority_queue {

    // static_assert(queue_size >= 1, "ERROR: Priority queue size less than 1.");

    // for Collect_smallest, the smallest number is the last element
    T queue[queue_size];

    // const Order order = Collect_smallest; 
    // constexpr int queue_size = queue_size;

    public: 

        Priority_queue() {
#pragma HLS inline
#pragma HLS array_partition variable=queue complete
            init();
        }

//         Priority_queue(T val) {
// #pragma HLS inline
// #pragma HLS array_partition variable=queue complete
//             init(val);
//         }

        void init() {
            // init the entire array, typically by huge numbers
#pragma HLS inline
            // init_loop: -> Triggers HLS bug: priority_queue.hpp:41) has multiple begin anchors.
            for (int i = 0; i < queue_size; i++) {
#pragma HLS pipeline II=1
                queue[i] = LARGE_NUM;
            }
        }

        void insert(T val) {
            // insert: single value version
#pragma HLS inline
            queue[0] = queue[0] < val? queue[0] : val;
            compare_swap_array_step_A();
            compare_swap_array_step_B();
        }

        void insert(hls::stream<T> &s_input) {
            // insert: from a stream
#pragma HLS inline
            float reg = s_input.read();
            queue[0] = queue[0] < reg? queue[0] : reg;
            compare_swap_array_step_A();
            compare_swap_array_step_B();
        }

        template<const int iter_num>
        void insert_range(hls::stream<T> &s_input) {
            // insert a range of numbers from a stream
#pragma HLS inline
            insert_range_loop:
            for (int i = 0; i < iter_num; i++) {
#pragma HLS pipeline II=1
                insert(s_input);
            }
        }

        void sort() {
            // after inserting the last element, the PQ is not necessarily sorted
            // it needs a few more operations to bubble the largest / smallest 
            // values in order
            // NOTE! sort() consumes extra logic, avoid it unless necessary
            for (int i = 0; i < queue_size; i++) {
                compare_swap_array_step_A();
                compare_swap_array_step_B();
            }
        }

        void get_result(hls::stream<T> &s_output) {
            // get the array out as a stream, the order is not guranteed, because
            // it needs a few more operations to bubble the largest / smallest 
            // after inserting the last element
#pragma HLS inline
            get_result_loop:
            for (int i = 0; i < queue_size; i++) {
#pragma HLS pipeline II=1
                s_output.write(queue[i]);
            }
        }
        
        void get_result_ascending_order(hls::stream<T> &s_output) {
#pragma HLS inline
            sort();
            get_result_ascending_order_loop:
            for (int i = 0; i < queue_size; i++) {
#pragma HLS pipeline II=1
                s_output.write(queue[queue_size - 1 - i]);
            }
        }
    

    private:
    
        void compare_swap(int idxA, int idxB) {
            // if smaller -> swap to right
            // note: idxA must < idxB
#pragma HLS inline
            if (queue[idxA] < queue[idxB]) {
                T regA = queue[idxA];
                T regB = queue[idxB];
                queue[idxA] = regB;
                queue[idxB] = regA;
            }
        }

        void compare_swap_array_step_A() {
            // start from idx 0, odd-even swap
#pragma HLS inline
            for (int j = 0; j < queue_size / 2; j++) {
#pragma HLS UNROLL
                compare_swap(2 * j, 2 * j + 1);
            }
        }
                    
        void compare_swap_array_step_B() {
            // start from idx 1, odd-even swap
#pragma HLS inline
            for (int j = 0; j < (queue_size - 1) / 2; j++) {
#pragma HLS UNROLL
                compare_swap(2 * j + 1, 2 * j + 2);
            }
        }
};
