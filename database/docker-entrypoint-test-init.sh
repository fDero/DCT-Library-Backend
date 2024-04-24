#! /bin/bash

psql=(psql -v ON_ERROR_STOP=1 --username "$POSTGRES_USER" --no-password --dbname "$POSTGRES_DB")

function scan_dir(){
    for f in $1/*; do 
        case "$f" in 
            *.sh) 
                if [ -x "$f" ]; then 
                    echo "$0: running $f" 
                    "$f"
                else 
                    echo "$0: sourcing $f" 
                    . "$f"
                fi 
                ;; 
            *.sql)    echo "$0: running $f"; "${psql[@]}" -f "$f"; echo ;; 
            *.sql.gz) echo "$0: running $f"; gunzip -c "$f" | "${psql[@]}"; echo ;; 
            *)        echo "$0: ignoring $f" ;; 
        esac 
        echo 
    done 
}

stdbuf -o0 printf "\033[34m---> BUILDING SCHEMA <---\x1b[0m\n"
scan_dir /docker-entrypoint-initdb.d/build_schema

"${psql[@]}" -c "call set_global('max_num_of_loans_per_user', ${MAX_LOANS_PER_USER});"

if [ "$MOCK_DATA" == "true" ]; then
    stdbuf -o0 printf "\033[34m---> MOCK DATA <---\x1b[0m\n"
    scan_dir /docker-entrypoint-initdb.d/mock_data
fi

if [ "$TEST" == "true" ]; then
    stdbuf -o0 printf "\033[34m---> INITIATING TESTS <---\x1b[0m\n"
    scan_dir /docker-entrypoint-initdb.d/test_init
fi