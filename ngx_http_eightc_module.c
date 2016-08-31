#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static char *ngx_http_eightc(ngx_conf_t *cf, void *post, void *data);

static ngx_conf_post_handler_pt ngx_http_eightc_p = ngx_http_eightc;

typedef struct {
    ngx_str_t   name;
} ngx_http_eightc_loc_conf_t;

static void *
ngx_http_eightc_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_eightc_loc_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_eightc_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    return conf;
}

static ngx_command_t ngx_http_eightc_commands[] = {
    { ngx_string("run_eightc"),
      NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_str_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_eightc_loc_conf_t, name),
      &ngx_http_eightc_p },

    ngx_null_command
};


static ngx_str_t eightc_string;
static ngx_http_module_t ngx_http_eightc_module_ctx = {
    NULL,                          /* preconfiguration */
    NULL,                          /* postconfiguration */

    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */

    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */

    ngx_http_eightc_create_loc_conf, /* create location configuration */
    NULL                           /* merge location configuration */
};

ngx_module_t ngx_http_eightc_module = {
    NGX_MODULE_V1,
    &ngx_http_eightc_module_ctx,    /* module context */
    ngx_http_eightc_commands,       /* module directives */
    NGX_HTTP_MODULE,               /* module type */
    NULL,                          /* init master */
    NULL,                          /* init module */
    NULL,                          /* init process */
    NULL,                          /* init thread */
    NULL,                          /* exit thread */
    NULL,                          /* exit process */
    NULL,                          /* exit master */
    NGX_MODULE_V1_PADDING
};

static ngx_int_t
ngx_http_eightc_handler(ngx_http_request_t *r)
{
    ngx_buf_t   *b;
    ngx_chain_t  out;

    size_t sz;
    char *strtmp = ngx_pcalloc(r->pool,eightc_string.len);
    strncpy(strtmp, (char*) eightc_string.data,eightc_string.len);

    char *args = ngx_pcalloc(r->pool,r->args.len);
    strncpy(args, (char*) r->args.data,r->args.len);

    char *strout = ngx_pcalloc(r->pool,100);
    int cells[1000];
    for(int i = 0;i<1000;i++){
      cells[i] = 0;
    }
    int cell = 0;

    int argn = 0;

    for(u_long i = 0;i<strlen(strtmp);i++){
      if(strtmp[i] == '+'){
        cells[cell] += 1;
      }else if(strtmp[i] == '-'){
        cells[cell] -= 1;
      }else if(strtmp[i] == '>'){
        cell += 1;
      }else if(strtmp[i] == '<'){
        cell -= 1;
      }else if(strtmp[i] == '.'){
        strout[strlen(strout)] = cells[cell];
      }else if(strtmp[i] == '['){
        if (cells[cell] == 0){
          while(strtmp[i]!=']'){
            i++;
          }
          i--;
        }
      }else if(strtmp[i] == ']'){
        if (cells[cell] != 0){
          while(strtmp[i]!='['){
            i--;
          }
          i--;
        }
      }else if(strtmp[i] == ','){
        cells[cell] = args[argn];
        argn ++;
      }
    }

    sz = strlen(strout);

    r->headers_out.content_type_len = sizeof("text/html") - 1;
    r->headers_out.content_type.data = (u_char *) "text/html";
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = sz;
    ngx_http_send_header(r);

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    out.buf = b;
    out.next = NULL;

    b->pos = (u_char*)strout;
    b->last = b->pos + sz;
    b->memory = 1;
    b->last_buf = 1;
    return ngx_http_output_filter(r, &out);
}

static char *
ngx_http_eightc(ngx_conf_t *cf, void *post, void *data)
{
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_eightc_handler;

    ngx_str_t  *name = data;

    if (ngx_strcmp(name->data, "") == 0) {
        return NGX_CONF_ERROR;
    }
    eightc_string.data = name->data;
    eightc_string.len = ngx_strlen(eightc_string.data);

    return NGX_CONF_OK;
}
