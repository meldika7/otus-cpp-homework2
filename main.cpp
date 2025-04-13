#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void reverseLexicSort(std::vector<std::vector<std::string> >& vec)
{
	auto reverseComparator = [](const std::vector<std::string>& left, 
	                            const std::vector<std::string>& right) -> bool 
	{
		if (left.size() != 4 || right.size() != 4)
			return false;	
		for(unsigned i = 0; i < left.size(); i++)
		{
			if (std::stoi(left[i]) == std::stoi(right[i]))
				continue;
			return std::stoi(left[i]) > std::stoi(right[i]);

		}
		return true; 
	};
	std::sort(vec.begin(), vec.end(), reverseComparator);
}

void printIpPool(std::vector<std::vector<std::string> >& vec)
{
	for(auto ip = vec.cbegin(); ip != vec.cend(); ++ip)
	{
		for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
		{
			if (ip_part != ip->cbegin())
			{
				std::cout << ".";

			}
			std::cout << *ip_part;
		}
		std::cout << std::endl;
	}
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
		reverseLexicSort(ip_pool);

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

		auto filter = [&ip_pool](int first, int second = -1) -> decltype(ip_pool)
		{
			decltype(ip_pool) res;
			for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
			{
				bool goodChoice = true;
				for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
				{
					if (ip_part == ip->cbegin() && std::atoi((*ip_part).c_str()) != first)
					{
						goodChoice = false;
						break;
					}
					if (ip_part == (ip->cbegin() + 1)) 
					{
						if (second == -1)
							break;
						if (std::atoi((*(ip_part + 1)).c_str()) == second)
						{
							goodChoice = false;
							break;
						}
					}
					
				}
				if (goodChoice)
				{
					res.push_back(*ip);				
				}
			}		
			return res;                        
	
		};

        // TODO filter by first byte and output
        auto ip = filter(1);
		printIpPool(ip);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}