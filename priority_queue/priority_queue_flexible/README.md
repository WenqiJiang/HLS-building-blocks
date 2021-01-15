# Priority Queue

## Version 1

```
    Priority_queue<float, PRIORITY_QUEUE_LEN, Collect_smallest> pq(LARGE_NUM);

    // pq.init(LARGE_NUM);
    pq.insert_range<STREAM_LEN>(s_input);
    pq.get_result(s_output);

```

```
+ Latency: 
    * Summary: 
    +---------+---------+-----------+-----------+------+------+----------+
    |  Latency (cycles) |   Latency (absolute)  |   Interval  | Pipeline |
    |   min   |   max   |    min    |    max    |  min |  max |   Type   |
    +---------+---------+-----------+-----------+------+------+----------+
    |     2062|     2062| 10.310 us | 10.310 us |  2053|  2053| dataflow |
    +---------+---------+-----------+-----------+------+------+----------+

    + Detail: 
        * Instance: 
        +--------------------+-------------------+---------+---------+-----------+-----------+------+------+---------+
        |                    |                   |  Latency (cycles) |   Latency (absolute)  |   Interval  | Pipeline|
        |      Instance      |       Module      |   min   |   max   |    min    |    max    |  min |  max |   Type  |
        +--------------------+-------------------+---------+---------+-----------+-----------+------+------+---------+
        |Loop_2_proc_U0      |Loop_2_proc        |     2052|     2052| 10.260 us | 10.260 us |  2052|  2052|   none  |
        |Loop_1_proc_U0      |Loop_1_proc        |       12|       12| 60.000 ns | 60.000 ns |    12|    12|   none  |
        |Loop_3_proc6_U0     |Loop_3_proc6       |       12|       12| 60.000 ns | 60.000 ns |    12|    12|   none  |
        |read_input_1024_U0  |read_input_1024_s  |     1034|     1034|  5.170 us |  5.170 us |  1034|  1034|   none  |
        |write_result_10_U0  |write_result_10_s  |       18|       18| 90.000 ns | 90.000 ns |    18|    18|   none  |
        |vadd_entry5_U0      |vadd_entry5        |        0|        0|    0 ns   |    0 ns   |     0|     0|   none  |
        +--------------------+-------------------+---------+---------+-----------+-----------+------+------+---------+

        * Loop: 
        N/A



================================================================
== Utilization Estimates
================================================================
* Summary: 
+---------------------+---------+-------+---------+---------+-----+
|         Name        | BRAM_18K| DSP48E|    FF   |   LUT   | URAM|
+---------------------+---------+-------+---------+---------+-----+
|DSP                  |        -|      -|        -|        -|    -|
|Expression           |        -|      -|        0|       81|    -|
|FIFO                 |        2|      -|      175|     1149|    -|
|Instance             |        4|      0|     5807|    11437|    -|
|Memory               |        -|      -|        -|        -|    -|
|Multiplexer          |        -|      -|        -|      144|    -|
|Register             |        -|      -|       25|        -|    -|
+---------------------+---------+-------+---------+---------+-----+
|Total                |        6|      0|     6007|    12811|    0|
+---------------------+---------+-------+---------+---------+-----+
|Available SLR        |     1344|   3008|   869120|   434560|  320|
+---------------------+---------+-------+---------+---------+-----+
|Utilization SLR (%)  |    ~0   |      0|    ~0   |        2|    0|
+---------------------+---------+-------+---------+---------+-----+
|Available            |     4032|   9024|  2607360|  1303680|  960|
+---------------------+---------+-------+---------+---------+-----+
|Utilization (%)      |    ~0   |      0|    ~0   |    ~0   |    0|
+---------------------+---------+-------+---------+---------+-----+

+ Detail: 
    * Instance: 
    +----------------------+--------------------+---------+-------+------+------+-----+
    |       Instance       |       Module       | BRAM_18K| DSP48E|  FF  |  LUT | URAM|
    +----------------------+--------------------+---------+-------+------+------+-----+
    |Loop_1_proc_U0        |Loop_1_proc         |        0|      0|   338|  2513|    0|
    |Loop_2_proc_U0        |Loop_2_proc         |        0|      0|  1360|  2625|    0|
    |Loop_3_proc6_U0       |Loop_3_proc6        |        0|      0|   363|   241|    0|
    |read_input_1024_U0    |read_input_1024_s   |        0|      0|   121|   168|    0|
    |vadd_control_s_axi_U  |vadd_control_s_axi  |        0|      0|  2486|  4520|    0|
    |vadd_entry5_U0        |vadd_entry5         |        0|      0|     3|    46|    0|
    |vadd_gmem0_m_axi_U    |vadd_gmem0_m_axi    |        2|      0|   512|   580|    0|
    |vadd_gmem34_m_axi_U   |vadd_gmem34_m_axi   |        2|      0|   512|   580|    0|
    |write_result_10_U0    |write_result_10_s   |        0|      0|   112|   164|    0|
    +----------------------+--------------------+---------+-------+------+------+-----+
    |Total                 |                    |        4|      0|  5807| 11437|    0|
    +----------------------+--------------------+---------+-------+------+------+-----+
```

## Version 2 -> everything together