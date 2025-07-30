#pragma once

// add your own read/write here

class c_driver 
{
public:
	unsigned long process_id = 0;
	unsigned long long process_base = 0;
	unsigned long long process_cr3 = 0;

	void* get_handle()
	{
		return nullptr;
	}

	void get_process(const char* process_name)
	{
		
	}

	void get_base_address()
	{
		
	}

	void get_cr3()
	{
		
	}

	void read_physical(void* address, void* buffer, unsigned long size)
	{
		
	}

	void write_physical(void* address, void* buffer, unsigned long size)
	{
		
	}

	bool get_valid_address(const unsigned long long address)
	{
		
	}

	template <typename T>
	T read(unsigned long long address) 
	{
		T buffer{ };
		return buffer;
	}

	template <typename T>
	void write(unsigned long long address, T buffer) 
	{

	}
};

inline c_driver driver;