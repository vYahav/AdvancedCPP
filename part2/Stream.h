#ifndef PART2_STREAM_H
#define PART2_STREAM_H
#include <functional>
#include <set>
#include <numeric>
#include <map>
#include <algorithm>

using namespace std;

template <typename T>
class Stream {
private:
    function<vector<T*>()> streamEval;

public:

    explicit Stream(function<vector<T*>()> stream) {
        streamEval=stream;
    };


    template<typename TContainer>
    static Stream<T> of (TContainer& cont) { // of - General cont
        //Create the stream
        auto stream = Stream<T>([cont]() {
            //Create and initialize new vector for the stream with cont's values
            vector<T*> vec(cont.size());
            std::copy(cont.begin(), cont.end(), vec.begin());

            //return vector
            return vec;
        });
        //Return stream
        return stream;
    }


    template <typename L>
    static Stream<T> of (map<L, T*>& cont) { // of - Map cont (edge case)
        //Create the stream
        auto stream = Stream<T>([cont]() {
            //Create new vector for the stream
            vector<T*> vec = vector<T*>();
            //Initialize vector with cont's values

            auto end=cont.end();
            auto iterator=cont.begin();
            while(iterator!=end){
                vec.push_back(iterator->second);
                iterator++;
            }
            //return the vector
            return vec;
        });
        //return the stream
        return stream;
    }







    Stream<T>& filter(function<bool(const T*)> predicat) { //Filter

        function<vector<T*>()> b4ChangeStream = streamEval;
        //Lazy eval'ed filtered stream.
        streamEval = [b4ChangeStream,predicat] () {
            //These are the procedures that receives a stream and a predicat, and returns a filtered stream.
            vector<T*> filteredMyResult;
            back_insert_iterator<vector<T*>> filteredMyResultWithBackInsertIterator = back_insert_iterator<vector<T*>>(filteredMyResult);
            vector<T*> vectorToFilter = b4ChangeStream();
            //If a value passes the predicat, copies the value to the filtered stream.
            auto first = vectorToFilter.begin();
            auto last = vectorToFilter.end();
            while (first!=last) {
                if (predicat(*first)) {
                    *filteredMyResultWithBackInsertIterator = *first;
                    filteredMyResultWithBackInsertIterator++;
                }
                first++;
            }

            //return the filtered stream.
            return filteredMyResult;
        };


        return *this;
    }


    Stream<T>& sorted(function<bool(const T* cmp1, const T* cmp2)> cmp){ //Sorted
        function<vector<T*>()> b4ChangeStream = streamEval;
        //Lazy eval'ed sorted stream.
        streamEval = [b4ChangeStream, cmp] () {
            //Transforms the stream to vector and sorts it with sort and than returns the sorted stream.
            vector<T*> sortedResult ( b4ChangeStream() );
            //Sort it.
            sort(sortedResult.begin(), sortedResult.end(), cmp);
            //Return sorted stream.
            return sortedResult;
        };
        return *this;
    }

    // --- NO NEED FOR PARENTS! I MADE THIS FOR THE TESTS ONLY --- DELETE THIS
    Stream<T>& sorted(){
        return sorted([](const T* a, const T* b){ return *a < *b;});
    }
    //-------------------------------------------------------------


    Stream<T>& distinct(function<bool(const T* a, const T* b)> distinctor){  //Distinct
        function<vector<T*>()> b4ChangeStream = streamEval;
        //Lazy eval'ed distincted stream.
        streamEval = [distinctor,b4ChangeStream] () {
            vector<T*> alreadyAppeared;
            bool wasIteratorSeen;

            vector<T*> myResult = b4ChangeStream();
            auto iterator = myResult.begin();
            //Iterate through stream
            while(iterator != myResult.end()) {

                //Check if iterator value was already seen
                wasIteratorSeen=false;
                auto first=alreadyAppeared.begin();
                auto last= alreadyAppeared.end();
                while (first!=last && !wasIteratorSeen) {
                    if (distinctor(*first,*iterator)){
                        wasIteratorSeen= true;
                    }
                    first++;
                }
                //end check

                //If iterator value already appeared in the past, then erase it
                if(wasIteratorSeen) {
                    myResult.erase(iterator);
                    continue;
                }
                //If iterator value has NOT already appeared in the past insert it to already appeared values vector and continue
                alreadyAppeared.push_back(*iterator);
                iterator++;

            }
            return myResult;
        };

        return *this;
    }



    // --- NO NEED FOR PARENTS! I MADE THIS FOR THE TESTS ONLY --- DELETE THIS
    Stream<T>& distinct(){
        return distinct([](const T*  a, const T* b){ return *a == *b;});
    }
    //-------------------------------------------------------------


    template <typename K>
    Stream<K> map(function<K*(const T*)> mapper) {   //Map
        function<vector<T*>()> b4ChangeStream = streamEval;

        //Lazy eval'ed mapped stream.
        auto temp= [b4ChangeStream, mapper] () {
            //Eval stream to be mapped
            vector<T*> beforeMap ( b4ChangeStream() );
            //Create vector to hold the new mapped stream
            vector<K*> afterMap;

            //Do the magic
            auto beforeMapIterator = beforeMap.begin();

            while (beforeMapIterator != beforeMap.end()) {
                afterMap.push_back(mapper(*beforeMapIterator));
                beforeMapIterator++;
            }

            return afterMap;
        };

        //Create the stream with our Lazy eval'ed mapped stream
        Stream<K> k(temp);

        //Return mapped stream.
        return k;
    }

    template <typename TContainer>
    TContainer collect() {      //Collect
        //Eval the stream
        auto stream = streamEval();
        //Transform its value into a TContainer
        TContainer cont(stream.size());
        std::copy(stream.begin(), stream.end(), cont.begin());
        //return the container
        return cont;
    }


    void forEach(function<void(T*)> operation) {        //forEach
        //Eval the stream
        vector<T*> stream = streamEval();
        //Iterate through every value in the stream and apply the function operation on it.
        auto iterator=stream.begin();
        auto end= stream.end();
        while(iterator!=end){
            operation(*iterator);
            iterator++;
        }
    }


    T* reduce(T* start, function<T*(const T* a, const T* b)> reduceFunc){  //Reduce
        //Eval the stream
        vector<T*> stream = streamEval();

        //Iterate through the stream from start to end and act like foldl.
        if(stream.empty()){return start;};

        auto iterator=stream.begin();
        auto end = stream.end();
        T* var=reduceFunc(start,*iterator);
        iterator++;
        while (iterator!=end) {
            var = reduceFunc(*iterator,var);
            iterator++;
        }

        //Return the final result variable
        return var;
    }



    int count () {      //Count
        //Eval the stream
        vector<T*> stream = streamEval();
        //Get size
        int size =(int) stream.size();

        //Return size
        return size;
    }







};


#endif //PART2_STREAM_H
