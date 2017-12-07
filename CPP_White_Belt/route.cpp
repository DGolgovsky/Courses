#include <vector>
#include <iostream>
#include <string>

using std::string;
using std::cout;

int computeDistance(const string& src, const string& dst)
{
#ifdef _DEBUG_
    std::cerr << "Computed distance: "<< dst << "(" << dst.length()
         << ") - "<< src << "(" << src.length()
         << ");" << std::endl;
#endif
    int dist = dst.length() - src.length();
    /* cmath abs() analogue */
    int minus_flag = dist >> 0x1F;
    dist = minus_flag ^ dist;
    dist -= minus_flag;
    return dist;
}

class Route
{
private:
    string source;
    string destination;
    int length;
    std::vector<string> compute_distance_log;
    void updateLength() {
        length = computeDistance(source, destination);
        compute_distance_log.push_back(
                source+ " - " + destination);
    }
public:
    Route(const string& src = "Moscow",
          const string& dst = "St. Petersburg")
        : source(src)
        , destination(dst)
    { updateLength(); }
    ~Route() {
#ifdef _DEBUG_
        for (const auto& entry: compute_distance_log) {
            std::cerr << "Points log: " << entry << "\n";
        }
#endif
    }
    string getSource() const {
        return source;
    }
    string getDestination() const {
        return destination;
    }
    int getLength() const {
        return length;
    }
    void setSource(const string& src) {
        source = src;
        updateLength();
    }
    void setDestination(const string& dst) {
        destination = dst;
        updateLength();
    }
    Route& operator=(const Route& route) {
        if (this != &route) {
            source = route.getSource();
            destination = route.getDestination();
            updateLength();
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Route& route) {
        os << "from '" << route.getSource()
            << "' to '" << route.getDestination()
            << "' is " << route.getLength() << " a.u.";
        return os;
    }
    void reverseRoute() {
        std::swap(source, destination);
    }
};

int main(void)
{
    Route trav_to("Kamyshin", "St. Petersburg");
    Route trav_from = {"New York", "Los Angeles"};
    Route trav_default;
    std::cout << "Route1:\n\t" << trav_to << "\n";
    trav_to.reverseRoute();
    std::cout << "Route2:\n\t"<< trav_from << "\n";
    std::cout << "Route3:\n\t"<< trav_default << "\n";
    std::cout << "Route1 after reverse:\n\t "
              << trav_to << "\n";
    return 0;
}
