#include "rakuten/rmcc/rmcc.h"

#include "rakuten/exception.h"

namespace rakuten{
  namespace rmcc {

    RomaValue::RomaValue(const char * data,long length,cas_t  cas)
      : data(data),length(length),cas(cas){
    }

    RomaConnection::node_info_list_t & RomaClient::get_nodelist(){
      return this->node_info_list;
    }
    const char * RomaClient::get_lasterror()const {
      return this->lasterr.str().c_str();
    }
    int RomaClient::num_valid_connection() const {
      return this->conn.num_valid();
    }
    void RomaClient::init(routing_mode_t routing_mode,unsigned long check_interval){
      try {
        this->conn.init(this->node_info_list,routing_mode,check_interval);
      }catch(const Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }
    void RomaClient::term(){
      try {
        this->conn.term();
      }catch(const Exception & ex ) {
        // @TEST There is no route to reach here yet. : this->conn.term() never throws Exception.
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }
    
    rmc_ret_t RomaClient::cmd_store(const char *key, RomaValue value, long exptime,long timeout){
      try {
        CmdSet cmd(key,0,exptime,value.data,value.length,timeout);
        cmd.prepare();
        conn.command(cmd);
        return cmd.roma_ret;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    rmc_ret_t RomaClient::cmd_add(const char *key, RomaValue value, long exptime,long timeout){
      try {
        CmdAdd cmd(key,0,exptime,value.data,value.length,timeout);
        cmd.prepare();
        conn.command(cmd);
        return cmd.roma_ret;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    rmc_ret_t RomaClient::cmd_replace(const char *key, RomaValue value, long exptime,long timeout){
      try {
        CmdReplace cmd(key,0,exptime,value.data,value.length,timeout);
        cmd.prepare();
        conn.command(cmd);
        return cmd.roma_ret;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    rmc_ret_t RomaClient::cmd_append(const char *key, RomaValue value, long exptime,long timeout){
      try {
        CmdAppend cmd(key,0,exptime,value.data,value.length,timeout);
        cmd.prepare();
        conn.command(cmd);
        return cmd.roma_ret;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    rmc_ret_t RomaClient::cmd_prepend(const char *key, RomaValue value, long exptime,long timeout){
      try {
        CmdPrepend cmd(key,0,exptime,value.data,value.length,timeout);
        cmd.prepare();
        conn.command(cmd);
        return cmd.roma_ret;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    rmc_ret_t RomaClient::cmd_cas(const char *key, RomaValue value, long exptime,cas_t cas,long timeout){
      try {
        CmdCas cmd(key,0,exptime,value.data,value.length,cas,timeout);
        cmd.prepare();
        conn.command(cmd);
        return cmd.roma_ret;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    rmc_ret_t RomaClient::cmd_delete(const char *key,long timeout){
      try {
        CmdDelete cmd(key,timeout);
        cmd.prepare();
        conn.command(cmd);
        return cmd.roma_ret;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    rmc_ret_t RomaClient::cmd_incr(const char *key, int param, long timeout){
      try {
	CmdIncr cmd(key,param,timeout);
	cmd.prepare();
	this->conn.command(cmd);
	if(cmd.roma_ret == RMC_RET_ERROR)
	  return -1;
	return cmd.value;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    rmc_ret_t RomaClient::cmd_decr(const char *key, int param, long timeout){
      try {
	CmdDecr cmd(key,param,timeout);
	cmd.prepare();
	this->conn.command(cmd);
	if(cmd.roma_ret == RMC_RET_ERROR)
	  return -1;
	return cmd.value;
      }catch(const rakuten::Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }
    
    RomaValue RomaClient::cmd_get(const char *key,long timeout){
      try {
        CmdGet cmd(key,timeout);
        cmd.prepare();
        this->conn.command(cmd);
        return cmd.value;
      }catch(const Exception & ex ) {
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }

    RomaValue RomaClient::cmd_gets(const char *key,long timeout){
      try {
        CmdGets cmd(key,timeout);
        cmd.prepare();
        this->conn.command(cmd);
        return cmd.value;
      }catch(const Exception & ex ) {
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }


    rmc_ret_t RomaClient::cmd_alist_sized_insert(const char *key, long size, RomaValue value,long timeout){
      try {
        CmdAlistSizedInsert cmd(key,size,value.data,value.length,timeout);
        cmd.prepare();
        this->conn.command(cmd);
        return cmd.roma_ret;
      }catch(const Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw;
      }
    }
    RomaValue RomaClient::cmd_alist_join(const char *key,const char * sep,long timeout){
      try {
        CmdAlistJoin cmd(key,sep,timeout);
        cmd.prepare();
        this->conn.command(cmd);
        return cmd.value;
      }catch(const Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw ex;
      }
    }
    rmc_ret_t RomaClient::cmd_alist_delete(const char *key,RomaValue value,long timeout){
      try {
        CmdAlistDelete cmd(key,value.data,value.length,timeout);
        cmd.prepare();
        this->conn.command(cmd);
        return cmd.roma_ret;
      }catch(const Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw;
      }
    }
    rmc_ret_t RomaClient::cmd_alist_delete_at(const char *key,int pos,long timeout){
      try {
        CmdAlistDeleteAt cmd(key,pos,timeout);
        cmd.prepare();
        this->conn.command(cmd);
        return cmd.roma_ret;
      }catch(const Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw;
      }
    }
    rmc_ret_t RomaClient::cmd_alist_clear(const char *key,long timeout){
      try {
	CmdAlistClear cmd(key,timeout);
	cmd.prepare();
        this->conn.command(cmd);
        return cmd.roma_ret;
      }catch(const Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw;
      }
    }
    rmc_ret_t RomaClient::cmd_alist_length(const char *key,long timeout){
      try {
	CmdAlistLength cmd(key,timeout);
	cmd.prepare();
	this->conn.command(cmd);
	if(cmd.roma_ret == RMC_RET_ERROR)
          return -1;
	return cmd.length;
      }catch(const Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw;
      }
    }
    rmc_ret_t RomaClient::cmd_alist_update_at(const char * key,int index,RomaValue value,long timeout){
      try {
	CmdAlistUpdateAt cmd(key,index,value.data,value.length,timeout);
	cmd.prepare();
        this->conn.command(cmd);
        return cmd.roma_ret;
      }catch(const Exception & ex ) {
        ERR_LOG(ex.get_msg());
        this->lasterr << ex.get_func() << ":" << ex.get_line() << ":" << ex.get_msg();
        throw;
      }
	
    }
  }
}
