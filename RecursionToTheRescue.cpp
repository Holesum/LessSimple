#include "RecursionToTheRescue.h"
#include "map.h"
#include <climits>
#include <iostream>
#include "Disasters.h"
using namespace std;

/* * * * Doctors Without Orders * * * */

/**
 * Given a list of doctors and a list of patients, determines whether all the patients can
 * be seen. If so, this function fills in the schedule outparameter with a map from doctors
 * to the set of patients that doctor would see.
 *
 * @param doctors  The list of the doctors available to work.
 * @param patients The list of the patients that need to be seen.
 * @param schedule An outparameter that will be filled in with the schedule, should one exist.
 * @return Whether or not a schedule was found.
 */
int numHoursDoc(Vector<Doctor> doctors){
	int sum;
	for(Doctor doc:doctors){
		sum += doc.hoursFree;
	}
	return sum;
}

int numHoursPat(Vector<Patient> patients){
	int sum;
	for(Patient pat : patients){
		sum += pat.hoursNeeded;
	}
	return sum;
}

bool canAllPatientsBeSeenHelper(Vector<Doctor>& doctors,
        Vector<Patient>& patients,
        Map<string, Set<string>>& schedule, int patCount){

	if(patCount == patients.size()){
		return true;
	} else {
		for(int i = 0; i < doctors.size();i++){
			if(patients[patCount].hoursNeeded <= doctors[i].hoursFree){
				doctors[i].hoursFree -= patients[patCount].hoursNeeded;

				if(canAllPatientsBeSeenHelper(doctors, patients, schedule, patCount + 1) == true){
					schedule[doctors[i].name].add(patients[patCount].name);
					return true;
				} else {
				doctors[i].hoursFree += patients[patCount].hoursNeeded;
				}
			}
		}
	}
	return false;
}

bool canAllPatientsBeSeen(const Vector<Doctor>& doctors,
                          const Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule) {

	if(numHoursPat(patients) > numHoursDoc(doctors)) return false;

	Vector<Doctor> tmpDocs = doctors;
	Vector<Patient> tmpPats = patients;
	bool flag = canAllPatientsBeSeenHelper(tmpDocs,tmpPats,schedule,0);

	return flag;

}

/* * * * Disaster Planning * * * */

/**
 * Given a transportation grid for a country or region, along with the number of cities where disaster
 * supplies can be stockpiled, returns whether it's possible to stockpile disaster supplies in at most
 * the specified number of cities such that each city either has supplies or is connected to a city that
 * does.
 * <p>
 * This function can assume that every city is a key in the transportation map and that roads are
 * bidirectional: if there's a road from City A to City B, then there's a road from City B back to
 * City A as well.
 *
 * @param roadNetwork The underlying transportation network.
 * @param numCities   How many cities you can afford to put supplies in.
 * @param locations   An outparameter filled in with which cities to choose if a solution exists.
 * @return Whether a solution exists.
 */
bool canBeMadeDisasterReadyHelper(Map<string, Set<string>> roadNetwork, int numCities, Set<string>& locations, Set<string> citiesLeft){
	if(citiesLeft.size() == 0){
		return true;
	}

	if(numCities == 0){
		return false;
	}

	else{
		string currCity = citiesLeft.first();
		for(string tmpCity : roadNetwork[currCity] + currCity){
			locations.add(tmpCity);
			if(canBeMadeDisasterReadyHelper(roadNetwork, numCities - 1, locations, citiesLeft - (roadNetwork[tmpCity] + tmpCity))){return true;}

			else locations.remove(tmpCity);

		}
		}
	return false;
}

bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& locations) {
	Set<string> cityLeft;

	for(string city : roadNetwork.keys()){
		cityLeft += city;
	}
	return canBeMadeDisasterReadyHelper(roadNetwork, numCities, locations, cityLeft);


}
