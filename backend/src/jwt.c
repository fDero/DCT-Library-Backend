// #include "jwt.h"

// char* jwt_private_key;
// char* jwt_public_key;
// char* jwt_iss;
// char* jwt_aud;
// long  jwt_exp;

// void jwt_init(){
// 		char* private_key = getenv("JWT_PRIVATE_KEY");
// 		jwt_private_key = (char*)malloc(strlen(private_key) + 1);
// 		strcpy(jwt_private_key, private_key);

// 		char* public_key = getenv("JWT_PUBLIC_KEY");
// 		jwt_public_key = (char*)malloc(strlen(public_key) + 1);
// 		strcpy(jwt_public_key, public_key);

// 		char* iss = getenv("JWT_ISS");
// 		jwt_iss = (char*)malloc(strlen(iss) + 1);
// 		strcpy(jwt_iss, iss);

// 		char* aud = getenv("JWT_AUD");
// 		jwt_aud = (char*)malloc(strlen(aud) + 1);
// 		strcpy(jwt_aud, aud);

// 		char* exp = getenv("JWT_EXP");
// 		jwt_exp = atol(exp);
// }

// void jwt_destroy(){
// 		free(jwt_private_key);
// 		free(jwt_public_key);
// 		free(jwt_iss);
// 		free(jwt_aud);
// }

// int jwt_free(char* jwt){
// 		return l8w8jwt_free(jwt);
// }

// char* jwt_encode(int account_id, char* session_token){
//     char* jwt;
//     size_t jwt_length;

// 		char account_id_str[20];
// 		sprintf(account_id_str, "%d", account_id);

//     // struct l8w8jwt_claim header_claims[] = {};

//     struct l8w8jwt_claim payload_claims[] =
//     {
// 				{
//             .key = "session-token",
//             .key_length = 13,
//             .value = session_token,
//             .value_length = strlen(session_token),
//             .type = L8W8JWT_CLAIM_TYPE_STRING
//         }
//     };

//     struct l8w8jwt_encoding_params params;
//     l8w8jwt_encoding_params_init(&params);

//     params.alg = L8W8JWT_ALG_ES256;

//     params.sub = account_id_str;
//     params.sub_length = strlen(account_id_str);

//     params.iss = jwt_iss;
//     params.iss_length = strlen(jwt_iss);

//     params.aud = jwt_aud;
//     params.aud_length = strlen(jwt_aud);

//     params.iat = l8w8jwt_time(NULL);
//     params.exp = l8w8jwt_time(NULL) + jwt_exp;

//     params.additional_header_claims = NULL;
//     params.additional_header_claims_count = 0;

//     params.additional_payload_claims = payload_claims;
//     params.additional_payload_claims_count = sizeof(payload_claims) / sizeof(struct l8w8jwt_claim);

//     params.secret_key = (unsigned char*)jwt_private_key;
//     params.secret_key_length = strlen(jwt_private_key);

//     params.out = &jwt;
//     params.out_length = &jwt_length;

//     if( l8w8jwt_encode(&params) != L8W8JWT_SUCCESS){
// 			l8w8jwt_free(jwt);
// 			return NULL;
// 		}
//     return jwt;
// }

// void jwt_decode(char* token, int account_id){
// 		if(token == NULL){
// 				return NULL;
// 		}
		
// 		char account_id_str[20];
// 		sprintf(account_id_str, "%d", account_id);

// 		struct l8w8jwt_decoding_params params;
//     l8w8jwt_decoding_params_init(&params);

//     params.alg = L8W8JWT_ALG_ES256;

//     params.jwt = (char*)token;
//     params.jwt_length = strlen(token);

//     params.verification_key = (unsigned char*)jwt_public_key;
//     params.verification_key_length = strlen(jwt_public_key);

//     params.validate_iss = jwt_iss;
//     params.validate_iss_length = strlen(jwt_iss);

//     params.validate_sub = account_id_str;
//     params.validate_sub_length = strlen(account_id_str);

// 		params.validate_aud = jwt_aud;
// 		params.validate_aud_length = strlen(jwt_aud);

//     params.validate_exp = 1;
//     params.exp_tolerance_seconds = 60;

//     params.validate_iat = 1;
//     params.iat_tolerance_seconds = 60;

//     enum l8w8jwt_validation_result validation_result;
//     int r = l8w8jwt_decode(&params, &validation_result, NULL, NULL);

//     printf("\nl8w8jwt_decode_es256 function returned %s (code %d).\n\nValidation result: \n%d\n", r == L8W8JWT_SUCCESS ? "successfully" : "", r, validation_result);
// }