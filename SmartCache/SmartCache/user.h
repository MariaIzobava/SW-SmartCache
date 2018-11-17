class User {

private:
	int id_;
	std::string name_;
	std::string mail_;

public:
	User(int id, std::string name, std::string mail):id_(id), name_(name), mail_(mail) {}
	~User() {}
};