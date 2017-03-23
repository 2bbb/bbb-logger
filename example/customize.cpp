#include <bbb/logger.hpp>

struct bar_separater : bbb::separater {
	std::string separate() { return " | "; };
};

struct custom_header : bbb::header {
	std::string head(std::string tag, bbb::log_level level) const {
		return "[HEAD] ";
	}
};

struct custom_footer : bbb::footer {
	std::string foot(std::string tag, bbb::log_level level) {
		return " [FOOT " + std::to_string(called_num++) + "]";
	}
    void reset() {
        called_num = 0UL;
    }
private:
    std::size_t called_num{0};
};

struct custom_formatter : bbb::header, bbb::footer {
	std::string head(std::string tag, bbb::log_level level) const {
		return "[FORMAT.head " + tag + "] ";
	}
	std::string foot(std::string tag, bbb::log_level level) const {
		return " [FORMAT.foot " + tag + "]";
	}
};

struct custom_stream : bbb::stream {
    std::ostream &os(bbb::log_level level) {
        return std::cerr << "custom_stream: ";
    }
};

bbb::custom_logger<custom_header, custom_footer, bar_separater> my_logger;
bbb::custom_logger<custom_formatter, bbb::elapsed_time_footer> time_logger;

int main(int argc, char *argv[]) {
    my_logger("my_logger") << "foo";
    my_logger("my_logger") << "bar";
    my_logger("my_logger") << "baz";
    my_logger.reset();
    my_logger("my_logger") << "reset!!";
    my_logger("my_logger") << "foo";
    my_logger("my_logger") << "bar";
    my_logger("my_logger") << "baz";
    my_logger.br();

    time_logger("time_logger") << "bar";
}