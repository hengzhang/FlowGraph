#ifndef FLOWGRAPH_WORKER_HPP
#define FLOWGRAPH_WORKER_HPP
#include <map>
#include <set>
#include <vector>
#include "barrier.hpp"
template <typename M>
struct message_router{
  void send(int dst, message<M> msg);
}
class worker {


  public:
    std::size_t id;
    master *m;
    std::size_t superstep = 0;
    std::size_t input_offset = 0;
    std::size_t input_len = 0;

    message_router *msg_router;
    std::set<std::size_t> active_vertexes;
    std::map<std::size_t, vertex> vertexes;
    std::map<std::size_t, vertex_state> states;
    std::map<std::size_t, std::vector<message> > messages;
    static flowgraph_barrier *sync;
    
    void setup(){
      msg_router = new message_router(){
        public void send(int dst, message<?> msg){
          int responsible = m.get_partition(dst);
          m->workers[resoponsible].malbox.add(msg);
        }
      };
    }

    worker(std::size_t id_in, master *m_in, vertex v_in):id(id_in),m(m_in){
      setup();
    }

    void set_input(std::size_t offset, std::size_t len){
      input_offset = offset;
      input_len = len;
    }

    void set_superstep(std::size_t superstep_in){
      superstep = superstep_in;
    }

    std::size_t get_superstep(){
      return superstep;
    }

    std::size_t get_active_vertexes(){
      return active_vertexes.size();
    }

    void read_input(){
      for(std::size_t i = input_offset; i< input_offset + input_len; i++){
        std::size_t vertex_id = i;
        std::list<std::size_t> vdata = graph_input.graph[vertex_id];
        std::size_t value = vdata.get(0);
        std::list<int> edgelist = vdata.

      }
    }



    void operator() (){
      read_input();
      do{
        read_inbox();
        compute_vertexes();
        sync.wait();
        
      }while(!master.is_done());
    
    }




};


#endif
