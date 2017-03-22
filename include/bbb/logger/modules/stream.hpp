#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../log_level.hpp"

namespace bbb {
	struct stream {
		std::ostream &os(log_level level) {
			switch(level) {
				case bbb::log_level::verbose:
				case bbb::log_level::info:
				case bbb::log_level::warning:
					return std::cout;
				default:
					return std::cerr;
			}
		}
	};
	
	struct error_stream : stream {
		std::ostream &os(log_level level) { return std::cerr; }
	};
	
	struct file_stream : stream {
		virtual ~file_stream() { if(ofs.is_open()) ofs.close(); }
		bool open(std::string path) {
			if(ofs.is_open()) ofs.close();
			
			ofs.open(path, std::ios::out | std::ios::app);
			if(ofs.fail()) {
				ofs.close();
				return false;
			} else {
				return true;
			}
		}
		std::ostream &os(log_level level) { return ofs; }
	private:
		std::ofstream ofs;
	};
	
	struct string_stream : stream {
		std::ostream &os() { return ss; }
		std::string text() { return ss.str(); }
		void clear() { ss.clear(); }
	private:
		std::stringstream ss;
	};
	
	struct null_stream : stream {
		std::ostream &os(log_level level) { return ofs; }
	private:
		std::ofstream ofs;
	};
};
