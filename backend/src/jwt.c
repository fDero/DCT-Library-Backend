#include "jwt.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <pthread.h>

char* JWT_PRIVATE_KEY;
char* JWT_PUBLIC_KEY;

char* JWT_ISS;
char* JWT_AUD;

float JWT_RENEWAL;
unsigned int JWT_EXP_BULLET;
unsigned int JWT_EXP_BLITZ;
unsigned int JWT_EXP_SHORT;
unsigned int JWT_EXP_MEDIUM;
unsigned int JWT_EXP_LONG;
unsigned int JWT_EXP_DEFAULT;

void jwt_init(){
    
    read_file(getenv("PRIVATE_KEY_FILE"), &JWT_PRIVATE_KEY);
    read_file(getenv("PUBLIC_KEY_FILE"), &JWT_PUBLIC_KEY);

    char* iss = getenv("JWT_ISS");
    JWT_ISS = (char*)malloc(strlen(iss) + 1);
    strcpy(JWT_ISS, iss);
    char* aud = getenv("JWT_AUD");
    JWT_AUD = (char*)malloc(strlen(aud) + 1);
    strcpy(JWT_AUD, aud);
    char* renewal = getenv("JWT_RENEWAL");
    JWT_RENEWAL = atof(renewal);
    JWT_EXP_BLITZ = atoi(getenv("JWT_EXP_BLITZ"));
    JWT_EXP_BULLET = atoi(getenv("JWT_EXP_BULLET"));
    JWT_EXP_SHORT = atoi(getenv("JWT_EXP_SHORT"));
    JWT_EXP_MEDIUM = atoi(getenv("JWT_EXP_MEDIUM"));
    JWT_EXP_LONG = atoi(getenv("JWT_EXP_LONG"));
    JWT_EXP_DEFAULT = atoi(getenv("JWT_EXP_DEFAULT"));
}

void encoded_jwt_destroy(char* jwt){
   return l8w8jwt_free(jwt);
}

char* jwt_encode(int account_id, const char* session_token, unsigned long exp_time){

    char* jwt;
	size_t jwt_length;

	char account_id_str[20];
	sprintf(account_id_str, "%d", account_id);

	char session_token_str[strlen(session_token) + 1];
	strcpy(session_token_str, session_token);
    char session_token_name[] = "session-token";

    struct l8w8jwt_claim payload_claims[] =
    {
        {
            .key = session_token_name,
            .key_length = 13,
            .value = session_token_str,
            .value_length = strlen(session_token_str),
            .type = L8W8JWT_CLAIM_TYPE_STRING
        }
    };

    struct l8w8jwt_encoding_params params;
    l8w8jwt_encoding_params_init(&params);

    params.alg = L8W8JWT_ALG_ES256;

    params.sub = account_id_str;
    params.sub_length = strlen(account_id_str);

    params.iss = JWT_ISS;
    params.iss_length = strlen(JWT_ISS);

    params.aud = JWT_AUD;
    params.aud_length = strlen(JWT_AUD);

    time_t now = l8w8jwt_time(NULL);
    params.iat = now;
    params.exp = now + exp_time;

    params.additional_header_claims = NULL;
    params.additional_header_claims_count = 0;

    params.additional_payload_claims = payload_claims;
    params.additional_payload_claims_count = sizeof(payload_claims) / sizeof(struct l8w8jwt_claim);

    params.secret_key = (unsigned char*)JWT_PRIVATE_KEY;
    params.secret_key_length = strlen(JWT_PRIVATE_KEY);

    params.out = &jwt;
    params.out_length = &jwt_length;

    if( l8w8jwt_encode(&params) != L8W8JWT_SUCCESS){
        l8w8jwt_free(jwt);
        return NULL;
    }
    return jwt;
}

decoded_jwt_t* jwt_decode(const char* jwt_token){
   
    char jwt_token_str[strlen(jwt_token) + 1];
    strcpy(jwt_token_str, jwt_token);

    if(jwt_token_str == NULL || sizeof(jwt_token_str) == 0){
      return NULL;
    }

    struct l8w8jwt_decoding_params params;
    l8w8jwt_decoding_params_init(&params);

    params.alg = L8W8JWT_ALG_ES256;

    params.jwt = jwt_token_str;
    params.jwt_length = strlen(jwt_token_str);

    params.verification_key = (unsigned char*)JWT_PUBLIC_KEY;
    params.verification_key_length = strlen(JWT_PUBLIC_KEY);

    params.validate_iss = JWT_ISS;
    params.validate_iss_length = strlen(JWT_ISS);

    params.validate_exp = 1;
    params.exp_tolerance_seconds = 60;

    params.validate_iat = 1;
    params.iat_tolerance_seconds = 60;

    struct l8w8jwt_claim* claims;
    size_t claims_count;

    enum l8w8jwt_validation_result validation_result;
    int r = l8w8jwt_decode(&params, &validation_result, &claims, &claims_count);
    
    if(r != L8W8JWT_SUCCESS){
        return NULL;
    }
  
    bool session_token_flag = false;
    bool account_id_flag = false;
    bool iss_flag = false;
    bool aud_flag = false;
    bool iat_flag = false;
    bool exp_flag = false;
    int recognized_claims_count = 0;

    decoded_jwt_t* decoded_jwt = (decoded_jwt_t*)malloc(sizeof(decoded_jwt_t));

    for(int i = 0; i < claims_count; i++){
        if (strcmp(claims[i].key, "session-token") == 0){
            alloc_and_strcpy(&(decoded_jwt->session_token), claims[i].value);
            session_token_flag = true;
            ++recognized_claims_count;
        }
        else if (strcmp(claims[i].key, "sub") == 0){
            decoded_jwt->account_id = atoi(claims[i].value);
            account_id_flag = true;
            ++recognized_claims_count;
        }
        else if (strcmp(claims[i].key, "iss") == 0){
            alloc_and_strcpy(&(decoded_jwt->iss), claims[i].value);
            iss_flag = true;
            ++recognized_claims_count;
        }
        else if (strcmp(claims[i].key, "aud") == 0){
            alloc_and_strcpy(&(decoded_jwt->aud), claims[i].value);
            aud_flag = true;
            ++recognized_claims_count;
        }
        else if (strcmp(claims[i].key, "iat") == 0){
            decoded_jwt->iat = atoi(claims[i].value);
            iat_flag = true;
            ++recognized_claims_count;
        }
        else if (strcmp(claims[i].key, "exp") == 0){
            decoded_jwt->exp = atoi(claims[i].value);
            exp_flag = true;
            ++recognized_claims_count;
        }
  }

    assert(session_token_flag && account_id_flag);
    assert(iss_flag && iat_flag && exp_flag);
    assert(recognized_claims_count == 6);
    return decoded_jwt;
}

void decoded_jwt_destroy(decoded_jwt_t* jwt){
	if(jwt == NULL){return;}
	free(jwt->session_token);
	free(jwt->iss);
	free(jwt->aud);
	free(jwt);
}

decoded_jwt_t* authorize_jwt(const char* jwt_str){
    decoded_jwt_t* jwt = jwt_decode(jwt_str);
	if(jwt == NULL){
		return NULL;
	}
    cache_conn_t* conn = (cache_conn_t*) pthread_getspecific(cache_connection_key);
    char* session_data = get_value_by_key_from_cache(conn, jwt->session_token);
    if (session_data == NULL || jwt->account_id != atoi(session_data)){
        return NULL;
    }
    return jwt;
}

bool is_jwt_about_to_expire(decoded_jwt_t* jwt){
    if(jwt == NULL){
        return true;
    }
    time_t now = l8w8jwt_time(NULL);
    return (jwt->exp - now) < (jwt->exp - jwt->iat) * JWT_RENEWAL;
}

unsigned long get_token_duration(const char* desired_exp){
    if(desired_exp == NULL){
        return JWT_EXP_DEFAULT;
    }
    if(strcmp(desired_exp, "bullet") == 0){
        return JWT_EXP_BULLET;
    }
    if(strcmp(desired_exp, "blitz") == 0){
        return JWT_EXP_BLITZ;
    }
    if(strcmp(desired_exp, "short") == 0){
        return JWT_EXP_SHORT;
    }
    if(strcmp(desired_exp, "medium") == 0){
        return JWT_EXP_MEDIUM;
    }
    if(strcmp(desired_exp, "long") == 0){
        return JWT_EXP_LONG;
    }
    return JWT_EXP_DEFAULT;
}