#include <bbb/logger.hpp>

int main(int argc, char *argv[]) {
	bbb::log.info() << "start";
	bbb::log.error() << "error and fatal out to stderr." << std::endl;

	bbb::log() << "most short hand style. default log_level is info.";
	bbb::log(bbb::log_level::warning) << "gives only log_level.";
	bbb::log("tag", bbb::log_level::info) << "can use with tag." << std::endl;

	bbb::set_log_level(bbb::log_level::warning);
	bbb::log.info() << "set_log_level(bbb::log_level::warning)";
	bbb::log.verbose("log_level") << "this is verbose level.";
	bbb::log.info("log_level") << "this is info level.";
	bbb::log.warning("log_level") << "this is warning level.";
	bbb::log.error("log_level") << "this is error level.";
	bbb::log.fatal("log_level") << "this is fatal level.";
	std::cout << std::endl;

	bbb::set_log_level(bbb::log_level::no_logging);
	bbb::log.info() << "set_log_level(bbb::log_level::no_logging) // all level will stop log.";
	bbb::log.verbose("log_level") << "this is verbose level.";
	bbb::log.info("log_level") << "this is info level.";
	bbb::log.warning("log_level") << "this is warning level.";
	bbb::log.error("log_level") << "this is error level.";
	bbb::log.fatal("log_level") << "this is fatal level.";
	std::cout << std::endl;

	bbb::set_log_level(bbb::log_level::verbose);
	bbb::log.info() << "set_log_level(bbb::log_level::verbose) // i.e. all level will do log.";
	bbb::log.verbose("log_level") << "this is verbose level.";
	bbb::log.info("log_level") << "this is info level.";
	bbb::log.warning("log_level") << "this is warning level.";
	bbb::log.error("log_level") << "this is error level.";
	bbb::log.fatal("log_level") << "this is fatal level.";
	std::cout << std::endl;

	bbb::log.set_header_time_format("%m/%d %T");
	bbb::log() << "time format is customizable.";
	bbb::log() << "see: http://en.cppreference.com/w/cpp/io/manip/put_time";
	bbb::log.set_default_tag("default_tag");
	bbb::log() << "default tag is customizable.";
	bbb::log.set_default_log_level(bbb::log_level::verbose);
	bbb::log() << "default log level is customizable.";
	
	// flog: file_logger
	std::string log_file_name = "log.txt";
	bbb::flog.open(log_file_name);
	bbb::flog() << "start";
	bbb::flog() << "this is logged in " << log_file_name << std::endl;

	// slog: string_logger
	bbb::slog() << "string logger start";
	bbb::slog() << "slog stores log texts.";
	bbb::slog() << "and get with bbb::slog.text()";
	std::cout << bbb::slog.text();
}