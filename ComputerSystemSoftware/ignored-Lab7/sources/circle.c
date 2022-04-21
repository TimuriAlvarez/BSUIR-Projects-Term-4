#include "circle.h"

void AppendCircle(struct Circle **to_append){
    struct Circle *SetRound;
    key_t key;

    if((*to_append) == nullptr)
        key = (key_t)rand()%100;
    else{
        struct Circle* GiveKey = shmat((*to_append)->left_shmid,nullptr,0);
        key = GiveKey->key + 1;
        shmdt(GiveKey);
    }
    
    int shmid;
	shmid=shmget(key, sizeof(struct Circle), 0666 | IPC_CREAT);
	SetRound = shmat(shmid,nullptr,0); //process attached to shared memory segment

    SetRound->added = 0;
    SetRound->deleted = 0;
    SetRound->message[0] = '\0';
    SetRound->key = key;
    SetRound->current_shmid = shmid;
    SetRound->checksum = 0;
    SetRound->current_shmid = shmid;
    if((*to_append) == nullptr){
        (*to_append) = SetRound;
        (*to_append)->left_shmid = shmid;
        (*to_append)->right_shmid = shmid;
    } else if ((*to_append)->right_shmid == (*to_append)->current_shmid){
        SetRound->left_shmid = (*to_append)->current_shmid;
        SetRound->right_shmid = (*to_append)->current_shmid;
        (*to_append)->right_shmid = shmid;
        (*to_append)->left_shmid = shmid;
    } else{
        //SetRound->right_shmid = (*to_append)->
        struct Circle *runner = shmat((*to_append)->left_shmid,nullptr,0);
        SetRound->right_shmid = runner->right_shmid;
        SetRound->left_shmid = (*to_append)->left_shmid;
        runner->right_shmid = shmid;
        (*to_append)->left_shmid = shmid;
        shmdt(runner);
    }
}