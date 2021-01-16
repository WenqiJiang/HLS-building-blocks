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
    

    // const Order order = Collect_smallest; 
    // constexpr int queue_size = queue_size;

    public: 

        Priority_queue() {
#pragma HLS inline
        }

        template<const int iter_num>
        void insert_wrapper(
            hls::stream<T> &s_input, 
            hls::stream<T> &s_output) {
            
            T queue[queue_size];
#pragma HLS array_partition variable=queue complete

            for (int i = 0; i < queue_size; i++) {
                queue[i] = LARGE_NUM;
            }

            insert: 
            for (int i = 0; i < iter_num; i++) {
#pragma HLS pipeline II=1
                T reg = s_input.read();
                queue[0] = queue[0] < reg? queue[0] : reg;

                // start from idx 0, odd-even swap
                for (int j = 0; j < queue_size / 2; j++) {
#pragma HLS UNROLL
                    compare_swap(queue, 2 * j, 2 * j + 1);
                }

                // start from idx 1, odd-even swap
                for (int j = 0; j < (queue_size - 1) / 2; j++) {
#pragma HLS UNROLL
                    compare_swap(queue, 2 * j + 1, 2 * j + 2);
                }
            }

            for (int i = 0; i < queue_size; i++) {
#pragma HLS pipeline II=1
                s_output.write(queue[i]);
            }
        }


    private:
    
        void compare_swap(T* array, int idxA, int idxB) {
            // if smaller -> swap to right
            // note: idxA must < idxB
#pragma HLS inline
            if (array[idxA] < array[idxB]) {
                T regA = array[idxA];
                T regB = array[idxB];
                array[idxA] = regB;
                array[idxB] = regA;
            }
        }

        void compare_swap_array_step_A(T* array) {
            // start from idx 0, odd-even swap
#pragma HLS inline
            for (int j = 0; j < queue_size / 2; j++) {
#pragma HLS UNROLL
                compare_swap(array, 2 * j, 2 * j + 1);
            }
        }
                    
        void compare_swap_array_step_B(T* array) {
            // start from idx 1, odd-even swap
#pragma HLS inline
            for (int j = 0; j < (queue_size - 1) / 2; j++) {
#pragma HLS UNROLL
                compare_swap(array, 2 * j + 1, 2 * j + 2);
            }
        }
};
