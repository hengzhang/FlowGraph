#ifndef FLOWGRAPH_WORKER_HPP
#define FLOWGRAPH_WORKER_HPP
#include <map>
#include <set>
#include <vector>
template <typename M>
struct message_router{
  void send(int dst, message<M> msg);
}
class worker{

  private:
    std::size_t id;
    master *m;
    std::size_t superstep;
    std::size_t input_offset;
    std::size_t input_len;

    std::map<std::size_t, vertex> vertexes;
    std::map<std::size_t, vertex_state> states;
    std::map<std::size_t, std::vector<message> > messages;


};


#endif
