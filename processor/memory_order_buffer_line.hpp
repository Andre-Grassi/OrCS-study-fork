class memory_order_buffer_line_t {
    public:
        uint64_t opcode_address;
        uint64_t memory_address;
        uint32_t memory_size;

        //HIVE
        bool is_hive;
        uint64_t read_address;
        uint64_t read2_address;
        uint64_t write_address;
         
        opcode_package_t* opcode_ptr; //USED FOR INSTRUCTION FETCH
        reorder_buffer_line_t* rob_ptr;                 /// rob pointer
        /// Memory Dependencies Control
        bool uop_executed; //*
        uint64_t uop_number;
        uint64_t readyAt;     //*                          // operation ready cycle time
        uint64_t cycle_send_request;                       // Cycle of send request
        package_state_t status; //*
        memory_operation_t memory_operation;
        uint64_t readyToGo;                                 /// Cycles of waiting
        uint32_t wait_mem_deps_number;                      /// Must wait BEFORE execution
        memory_order_buffer_line_t* *mem_deps_ptr_array;    /// Elements to wake-up AFTER execution
        //==========================================================================================
        uint32_t processor_id;                              // id of processor make request 
        uint64_t cycle_sent_to_DRAM;
        //==========================================================================================
        //Control variables
        bool processed; 
        bool sent; //*
        bool forwarded_data;
        bool waiting_DRAM;
        bool core_generate_miss;
        // ====================================================================
        /// Methods
        // ====================================================================
        memory_order_buffer_line_t();
        ~memory_order_buffer_line_t();

        void package_clean();
        std::string content_to_string();
        //select packages
        static int32_t find_free(memory_order_buffer_line_t *input_array, uint32_t size_array);
        static int32_t find_old_request_state_ready(memory_order_buffer_line_t *input_array, uint32_t size_array, package_state_t state);
        static void printAllOrder(memory_order_buffer_line_t* input_array, uint32_t size_array,uint32_t start,uint32_t end);

        // =====================================================================
        // Update status
        // =====================================================================
        void updatePackageUntrated(uint32_t stallTime);
        void updatePackageReady(uint32_t stallTime);
        void updatePackageWait(uint32_t stallTime);
        void updatePackageFree(uint32_t stallTime);
};
