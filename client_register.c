#include "include/client_register.h"

// ===========================================================================
// create_client_register
// ===========================================================================
int create_client_register(clientRegister **clReg){
   *clReg = malloc(sizeof(clientRegister));
   if(!(clReg)){
      fprintf(stderr, "create_client_register: error while allocating memory.\n");
      return PROG_ERROR;
   }
   if(cnl_create(&((*clReg)->nodeList)) == PROG_ERROR){
      fprintf(stderr, "create_client_register: error while creating the client node list.\n");
      return PROG_ERROR;
   }
   if(cpt_create(&((*clReg)->treeRoot)) == PROG_ERROR){
      fprintf(stderr, "create_client_register: error while creating the path tree.\n");
      return PROG_ERROR;
   }
   return PROG_SUCCESS;
}

// ===========================================================================
// cr_register_path
// ===========================================================================
int cr_register_path(clientRegister *clReg, clientData *data, char *path, registrationMode mod){
   return cpt_add_client_registration(clReg->treeRoot, path, clReg->nodeList, data, mod);
}

// ===========================================================================
// cr_unregister_path
// ===========================================================================
int cr_unregister_path(clientRegister *clReg, clientData *data, char *path){
   return cpt_remove_client_registration(clReg->treeRoot, path, clReg->nodeList, data);
}

// ===========================================================================
// print_client_register [DEBUG]
// ===========================================================================
void print_client_register(clientRegister *cr){
   cpt_print_tree(cr->treeRoot);
   cnl_print_list(cr->nodeList);
}
