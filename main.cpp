#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

int main(){
    //  initializing a json object
    nlohmann::json movieData = {
        {
            "Sherlock", {
                {"country", "Great Britain, USA"},
                {"year", "2010"},
                {"studio", "Hartswood Films"},
                {"scriptwriter", "Mark Gatiss"},
                {"director", "Paul McGuigan"},
                {"producer", "Steven Moffat"},
                {"actors", {
                    {"role 1", "Benedict Cumberbatch"},
                    {"role 2", "Martin Freeman"},
                    {"role 3", "Una Stubbs"},
                    {"role 4", "Rupert Graves"},
                    {"role 5", "Louise Briley"},
                    {"role 6", "Mark Gatiss"},
                    {"role 7", "Andrew Scott"},
                    {"role 8", "Amanda Abbington"},
                    {"role 9", "Jonathan Aris"},
                    {"role 10", "Wynette Robinson"}
                }}
            }
        },
        {
            "Fisher", {
                {"country", "Russia"},
                {"year", "2023"},
                {"studio", "Studio 812"},
                {"scriptwriter", "Sergey Kalvarsky"},
                {"director", "Sergey Taramaev"},
                {"producer", "Fyodor Bondarchuk"},
                {"actors", {
                    {"role 1", "Ivan Yankovsky"},
                    {"role 2", "Alexandra Bortich"},
                    {"role 3", "Alexander Yatsenko"},
                    {"role 4", "Sergey Gilev"},
                    {"role 5", "Anna Snatkina"},
                    {"role 6", "Roman Evdokimov"},
                    {"role 7", "Olga Ozollapinya"},
                    {"role 8", "Alexey Grishin"},
                    {"role 9", "Stanislav Solomatin"},
                    {"role 10", "Diana Milutina"}
                }}
            }
        },
        {
            "The Black Box", {
                {"country", "France"},
                {"year", "2020"},
                {"studio", "Epinay Studios"},
                {"scriptwriter", "Nicolas Beauvais-Levrard"},
                {"director", "Jan Gozlan"},
                {"producer", "Vassim Beji"},
                {"actors", {
                    {"role 1", "Pierre Ninet"},
                    {"role 2", "Lou de Laage"},
                    {"role 3", "André Dussollier"},
                    {"role 4", "Sebastien Poudroux"},
                    {"role 5", "Olivier Rabourdain"},
                    {"role 6", "Guillaume Marquet"},
                    {"role 7", "Mehdi Javadi"},
                    {"role 8", "Anne Azoulay"},
                    {"role 9", "Aurelien Recoine"},
                    {"role 10", "Gregory Deranger"}
                }}
            }
        },
        {
            "The Adventures of Sherlock Holmes and Dr. Watson: The Hound of the Baskervilles", {
                {"country", "the USSR"},
                {"year", "1981"},
                {"studio", "Lenfilm in Leningrad"},
                {"scriptwriter", "Igor Maslennikov"},
                {"director", "Igor Maslennikov"},
                {"producer", "Igor Maslennikov"},
                {"actors", {
                    {"role 1", "Vasily Livanov"},
                    {"role 2", "Vitaly Solomin"},
                    {"role 3", "Nikita Mikhalkov"},
                    {"role 4", "Oleg Yankovsky"},
                    {"role 5", "Irina Kupchenko"},
                    {"role 6", "Alexander Adabashyan"},
                    {"role 7", "Svetlana Kryuchkova"},
                    {"role 8", "Alla Demidova"},
                    {"role 9", "Evgeny Steblov"},
                    {"role 10", "Sergey Martinson"}
                }}
            }
        },
        {
            "Wind River", {
                {"country", "Great Britain, France, USA"},
                {"year", "2016"},
                {"studio", "filmed in Utah"},
                {"scriptwriter", "Taylor Sheridan"},
                {"director", "Taylor Sheridan"},
                {"producer", "Braden Aftegood"},
                {"actors", {
                    {"role 1", "Jeremy Renner"},
                    {"role 2", "Elizabeth Olsen"},
                    {"role 3", "Graham Greene"},
                    {"role 4", "Gil Birmingham"},
                    {"role 5", "Jon Bernthal"},
                    {"role 6", "Julia Jones"},
                    {"role 7", "Kelsey Esbel"},
                    {"role 8", "Theo Briones"},
                    {"role 9", "Apesanahquat"},
                    {"role 10", "Tantu Cardinal"}
                }}
            }
        }
    };

    // creating a json file
    std::ofstream outputStream("../movie.json");
    outputStream << movieData;
    outputStream.close();

    // reading from a json data file
    std::ifstream inputStream("../movie.json");
    movieData = nlohmann::json::parse(inputStream);
    inputStream.close();

    // enter a name to search for
    std::string nameForSearch;
    std::cout << "Enter name or surname for searching: ";
    std::cin >> nameForSearch;

    // converting string characters to lowercase
    std::transform(
        nameForSearch.begin(), nameForSearch.end(),
        nameForSearch.begin(),
        ::tolower
    );

    // description of the structure of the found element
    struct List {
        std::string film;  // The name of the film
        std::string role;  // role
    };
    std::vector<List> list;  // list of found items

    // the cycle of the passage through the films
    list.clear();
    for(nlohmann::json::iterator ms = movieData.begin(); ms != movieData.end(); ms++) {
        nlohmann::json movie = ms.value();  // movie data
        bool isFound = false;  // let's say that we didn't find the structure - the list of roles

        // the cycle of passing through the data elements of the film (we are looking for a list of roles - structure)
        for(nlohmann::json::iterator as = movie.begin(); (as != movie.end()) && !isFound; as++) {
            nlohmann::json actors = as.value();  // the list of roles

            // if this object is a structure, then this is a list of roles
            if(isFound = actors.is_structured()) {
                // the cycle of passage through the roles of the film
                for(nlohmann::json::iterator ar = actors.begin(); ar != actors.end(); ar++) {
                    // taking the name of the role performer
                    std::string actualNameLower = ar.value();
                    // and reducing the characters of the string to lowercase
                    std::transform(
                        actualNameLower.begin(), actualNameLower.end(),
                        actualNameLower.begin(),
                        ::tolower
                    );
                    // if the first or last name matches, then add the information to the list
                    if(actualNameLower.find(nameForSearch) != std::string::npos) {
                        list.push_back({ms.key(), ar.key()});
                        break;
                    }
                }
            }
        }
    }


    // if the search result list is empty
    if(list.size() == 0) {
        // then output the corresponding message
        std::cout << "Data about that actor was not found" << std::endl;
    } else {
        // otherwise, output the result
        std::cout
            << "We found information about " << nameForSearch << std::endl
            << "This actor has starred in the following films:" << std::endl;        
        for(int i=0; i<list.size(); i++) {
            List *elem = &list[i];
            std::cout << elem->film << " - " << elem->role << std::endl;
        }
    }

    // output of the program shutdown message
    std::cout
        << "----------------------------------------------------------\n"
        << "Done.\n";

    return 0;
}
