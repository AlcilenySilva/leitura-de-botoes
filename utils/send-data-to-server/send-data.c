#include "send-data.h"
#include "lwip/ip4_addr.h"
#include <stdlib.h>
#include <string.h>

#define SERVER_IP "192.168.0.77"
#define SERVER_PORT 3000
#define SERVER_PATH "/receber"

// Callback quando o servidor envia resposta
static err_t recv_callback(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err) {
    if (!p) {
        printf("Conexão encerrada pelo servidor\n");
        tcp_close(pcb);
        free(arg); // liberar memória alocada
        return ERR_OK;
    }

    char buffer[512];
    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, p->payload, p->len);
    printf("Resposta do servidor:\n%s\n", buffer);

    pbuf_free(p);
    tcp_close(pcb);
    free(arg); // liberar após resposta
    return ERR_OK;
}

// Callback quando os dados são enviados
static err_t sent_callback(void *arg, struct tcp_pcb *pcb, u16_t len) {
    printf("Dados enviados com sucesso!\n");
    return ERR_OK;
}

// Callback quando a conexão com o servidor é estabelecida
static err_t connect_callback(void *arg, struct tcp_pcb *pcb, err_t err) {
    printf("Callback de conexão chamado. err = %d\n", err);

    if (err != ERR_OK) {
        printf("Erro ao conectar ao servidor (callback)\n");
        tcp_abort(pcb);
        free(arg);
        return err;
    }

    char *request_body = (char *)arg;

    char request[1024]; 
    snprintf(request, sizeof(request),
             "POST %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %d\r\n"
             "\r\n"
             "%s",
             SERVER_PATH, SERVER_IP, strlen(request_body), request_body);
    
    printf("Requisição montada:\n%s\n", request); 

    tcp_sent(pcb, sent_callback);
    tcp_recv(pcb, recv_callback);

    err_t write_err = tcp_write(pcb, request, strlen(request), TCP_WRITE_FLAG_COPY);
    if (write_err != ERR_OK) {
        printf("tcp_write falhou com erro: %d\n", write_err);
        tcp_abort(pcb);
        free(arg);
        return ERR_ABRT;
    }

    err_t output_err = tcp_output(pcb);
    if (output_err != ERR_OK) {
        printf("tcp_output falhou com erro: %d\n", output_err);
        tcp_abort(pcb);
        free(arg);
        return ERR_ABRT;
    }
    return ERR_OK;
}

// Função que inicia a conexão TCP
void send_data_to_server(const char *path, char *request_body, const char *type_method) {
    struct tcp_pcb *pcb = tcp_new();
    if (!pcb) {
        printf("Erro ao criar PCB\n");
        free(request_body); // importante para evitar vazamento se pcb falhar
        return;
    }

    ip_addr_t server_ip;
    ip4addr_aton(SERVER_IP, &server_ip);

    tcp_arg(pcb, request_body); // envia a string alocada como contexto

    if (tcp_connect(pcb, &server_ip, SERVER_PORT, connect_callback) != ERR_OK) {
        printf("Erro ao conectar ao servidor\n");
        tcp_abort(pcb);
        free(request_body);
        return;
    }
}

// Função que monta o JSON e chama o envio
void create_request(const char *status, int total, float temperatura) {
    const char *type_method = "POST";
    const char *path = SERVER_PATH;
    char temp_json[256];

    snprintf(temp_json, sizeof(temp_json),
             "{ \"status\": \"%s\", \"total\": %d, \"temperatura\": %.1f }",
             status, total, temperatura);

    // Alocar memória dinamicamente
    char *json_copy = malloc(strlen(temp_json) + 1);
    if (!json_copy) {
        printf("Erro ao alocar memória\n");
        return;
    }
    strcpy(json_copy, temp_json);

    printf("Enviando para http://%s:%d%s -> %s\n", SERVER_IP, SERVER_PORT, SERVER_PATH, temp_json);

    send_data_to_server(path, json_copy, type_method);
}