#ifndef QUESTION5_H
#define QUESTION5_H
#include <vector>
#include <list>

// Represents a graph object
class graph 
{
    private:
        int size;
        std::vector< std::list<int> > adj_list;
        std::vector< char > labels;
        void depth_first( int ) const;
        
    public:
        graph( const char* filename );
        ~graph();
        int get_size() const;
        void traverse( ) const;
        void print ( ) const;
};

#endif 
