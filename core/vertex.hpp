#ifndef FLOWGRAPH_VERTEX_HPP
#define FLOWGRAPH_VERTEX_HPP

#include <List>

namespace flow_graph{
  template<typename M>
  class vertex{
    //vertex():state(NULL){}
    vertex(vertex_state *state_in):state(state_in){
    
    }
    void set_state(vertex_state *state_in){
      state = state_in;
    }
    std::size_t get_value(){
      return state->value;
    }
    void set_value(std::size_t value_in){
      state->value = value_in;
    }
    std::size_t get_superstep(){
      return state.get_superstep();
    }
    std::vector<std::size_t> get_outedges(){
      return state.get_outedges();
    }
    std::size_t get_id(){
      return state.get_id();
    }
    void send_msg(std::size_t dst, M msg){
      std::size_t ss = get_superstep();
      message *m = new message<M>(ss, dst, msg);
      state.get_message_router().send(dst, m);
    }
    void vote_to_halt(){
      state.set_active(false);
    }
    void log(string text){
      std::cout<<"["<<get_id()<<"]"<<text;
    }
    //Interface of compute
    void compute(std::list<message<M> > messages){}

    private:
      vertex_state *state;
  };

  class vertex_state{
    vertex_state(int vid_in, 
        worker *w_in, 
        std::size_t value_in, 
        std::list<std::size_t> edges_in)
      :vid(vid_in), w(w_in), value(value_in), edges(edges_in){}

    std::list<std::size_t> get_edges(){
      return edges;
    }
    void set_active(bool active_in){
      if(active && !active_in){
        active = false;
        w.active_vertexes.remove(vid);
      } else if( !active && active_in){
        active = true;
        w.active_vertexes.add(vid);
      }
    }
    std::size_t get_id(){
      return vid;
    }
    std::size_t get_superstep(){
      return w.get_superstep();
    }
    bool is_active(){
      return active;
    }
    message_router get_message_router(){
      return w.msg_router;
    }
    string log(){
      return "["+ active+"]"+value;
    }

    public:
      std::size_t value;
    private:
      std::size vid;
      bool active;
      std::list<std::size_t> edges;
      worker *w;
  }
}
#endif
