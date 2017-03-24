/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/builtin_modules/streams.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <bbb/logger/log_level.hpp>
#include <bbb/logger/modules/stream.hpp>

namespace bbb {
	namespace loggers {
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
			std::ostream &os(log_level level) { return ss; }
			std::string text() { return ss.str(); }
			void clear() { ss.clear(); }
		private:
			std::stringstream ss;
		};
		
		struct null_streambuf : public std::streambuf {
		private:
			virtual int overflow(char c) {
				return traits_type::not_eof(c);
			}
		};
		
		struct null_ostream : public std::ostream {
			null_streambuf streambuf;
		public:
			null_ostream() : std::ostream(&streambuf){}
		};
		static null_ostream nout;

		struct null_stream : stream {
			std::ostream &os(log_level level) { return nout; }
		};
	};
};
