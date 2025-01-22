[![build](https://github.com/adamyg/memcached-win32/actions/workflows/build.yml/badge.svg)](https://github.com/adamyg/memcached-win32/actions/workflows/build.yml)

[![Build status](https://ci.appveyor.com/api/projects/status/6fq5on94pp3i87kj?svg=true&passingText=MSVC%20Passing&failingText=MSVC%20Failing&pendingText=MSVC%20Pending)](https://ci.appveyor.com/project/adamyg/memcached-win32-msvc/)

# memcached-win32

memcached 1.6.34 windows service, with TLS and Lua based builtin proxy features enabled; 32 and 64 bit builds.

# usage

Download and extract into a working directory, for example ```c:\memcached```

## install and uninstall

```
memcached_service -d install
memcached_service -d uninstall
```

## start/stop

```
memcached_service -d start
memcached_service -d stop
```

## run as non-service

```
memcached_service -d run
```

# help

```
memcached-win32 - Windows Memcached Service 1.6.34, service options

NAME:

memcached_service - high-performance memory object caching system

SYNOPSIS:

memcached_service [options] <command> [configuration]

OPTIONS:

-S, --service=<name>      Service name.
-Z, --config-file <file>  Configuration file.
-N, --noconfig            Ignore service configuration file/registry.
-p, --port=<num>          Service port; utilised for port specific configuration.

Following are effective when running under a console:

-d, --daemon              Hide console.
--no-logger               Control logger and associated stdout/sterr redirection.
--stdout                  Redirect to both logger and console.

COMMANDS:

version                   Service version information.
install                   Install as a service; see 'install help' for details.
uninstall                 Uninstall service.
config <attribute>        Config service attributes; see 'config help' for details.
control <action>          Service control functions; see 'control help' for details
run <configuration>       Run the service.

CONFIGURATION:

These programs follow the usual UNIX command line syntax. A summary of configuration options is
included below. These may also be declared within the configuration file

memcached 1.6.34
-p, --port=<num>          TCP port to listen on (default: 11211)
-U, --udp-port=<num>      UDP port to listen on (default: 0, off)
-A, --enable-shutdown     enable ascii "shutdown" command
-l, --listen=<addr>       interface to listen on (default: INADDR_ANY)
                          if TLS/SSL is enabled, 'notls' prefix can be used to
                          disable for specific listeners (-l notls:<ip>:<port>) 
-d, --daemon              run as a daemon
-r, --enable-coredumps    maximize core file limit
-u, --user=<user>         assume identity of <username> (only when run as root)
-m, --memory-limit=<num>  item memory in megabytes (default: 64)
-M, --disable-evictions   return error on memory exhausted instead of evicting
-c, --conn-limit=<num>    max simultaneous connections (default: 1024)
-k, --lock-memory         lock down all paged memory
-v, --verbose             verbose (print errors/warnings while in event loop)
-vv                       very verbose (also print client commands/responses)
-vvv                      extremely verbose (internal state transitions)
-h, --help                print this help and exit
-i, --license             print memcached and libevent license
-V, --version             print version and exit
-P, --pidfile=<file>      save PID in <file>, only used with -d option
-f, --slab-growth-factor=<num> chunk size growth factor (default: 1.25)
-n, --slab-min-size=<bytes> min space used for key+value+flags (default: 48)
-L, --enable-largepages  try to use large memory pages (if available)
-D <char>     Use <char> as the delimiter between key prefixes and IDs.
              This is used for per-prefix stats reporting. The default is
              ":" (colon). If this option is specified, stats collection
              is turned on automatically; if not, then it may be turned on
              by sending the "stats detail on" command to the server.
-t, --threads=<num>       number of threads to use (default: 4)
-R, --max-reqs-per-event  maximum number of requests per event, limits the
                          requests processed per connection to prevent 
                          starvation (default: 20)
-C, --disable-cas         disable use of CAS
-b, --listen-backlog=<num> set the backlog queue limit (default: 1024)
-B, --protocol=<name>     protocol - one of ascii, binary, or auto (default: auto-negotiate)
-I, --max-item-size=<num> adjusts max item size
                          (default: 1m, min: 1k, max: 1024m)
-F, --disable-flush-all   disable flush_all command
-X, --disable-dumping     disable stats cachedump and lru_crawler metadump
-W  --disable-watch       disable watch commands (live logging)
-Y, --auth-file=<file>    (EXPERIMENTAL) enable ASCII protocol authentication. format:
                          user:pass\nuser2:pass2\n
-e, --memory-file=<file>  (EXPERIMENTAL) mmap a file for item memory.
                          use only in ram disks or persistent memory mounts!
                          enables restartable cache (stop with SIGUSR1)
-Z, --enable-ssl          enable TLS/SSL
-o, --extended            comma separated list of extended options
                          most options have a 'no_' prefix to disable
   - maxconns_fast:       immediately close new connections after limit (default: enabled)
   - hashpower:           an integer multiplier for how large the hash
                          table should be. normally grows at runtime. (default starts at: 0)
                          set based on "STAT hash_power_level"
   - tail_repair_time:    time in seconds for how long to wait before
                          forcefully killing LRU tail item.
                          disabled by default; very dangerous option.
   - hash_algorithm:      the hash table algorithm
                          default is murmur3 hash. options: jenkins, murmur3, xxh3
   - no_lru_crawler:      disable LRU Crawler background thread.
   - lru_crawler_sleep:   microseconds to sleep between items
                          default is 100.
   - lru_crawler_tocrawl: max items to crawl per slab per run
                          default is 0 (unlimited)
   - read_buf_mem_limit:  limit in megabytes for connection read/response buffers.
                          do not adjust unless you have high (20k+) conn. limits.
                          0 means unlimited (default: 0)
   - no_lru_maintainer:   disable new LRU system + background thread.
   - hot_lru_pct:         pct of slab memory to reserve for hot lru.
                          (requires lru_maintainer, default pct: 20)
   - warm_lru_pct:        pct of slab memory to reserve for warm lru.
                          (requires lru_maintainer, default pct: 40)
   - hot_max_factor:      items idle > cold lru age * drop from hot lru. (default: 0.20)
   - warm_max_factor:     items idle > cold lru age * this drop from warm. (default: 2.00)
   - temporary_ttl:       TTL's below get separate LRU, can't be evicted.
                          (requires lru_maintainer, default: 61)
   - idle_timeout:        timeout for idle connections. (default: 0, no timeout)
   - slab_chunk_max:      (EXPERIMENTAL) maximum slab size in kilobytes. use extreme care. (default: 512)
   - watcher_logbuf_size: size in kilobytes of per-watcher write buffer. (default: 256)
   - worker_logbuf_size:  size in kilobytes of per-worker-thread buffer
                          read by background thread, then written to watchers. (default: 64)
   - track_sizes:         enable dynamic reports for 'stats sizes' command.
                          note that counts for each size are approximate.
   - no_hashexpand:       disables hash table expansion (dangerous)
   - modern:              enables options which will be default in future.
                          currently: nothing
   - no_modern:           uses defaults of previous major version (1.4.x)

   - External storage (ext_*) related options (see: https://memcached.org/extstore)
   - ext_path:            file to write to for external storage.
                          ie: ext_path=/mnt/d1/extstore:1G
   - ext_page_size:       size in megabytes of storage pages. (default: 64)
   - ext_wbuf_size:       size in megabytes of page write buffers. (default: 4)
   - ext_threads:         number of IO threads to run. (default: 1)
   - ext_item_size:       store items larger than this (bytes, default 512)
   - ext_item_age:        store items idle at least this long (seconds, default: no age limit)
   - ext_low_ttl:         consider TTLs lower than this specially (default: 0)
   - ext_drop_unread:     don't re-write unread values during compaction (default: disabled)
   - ext_recache_rate:    recache an item every N accesses (default: 2000)
   - ext_compact_under:   compact when fewer than this many free pages
                          (default: 1 percent of the assigned storage)
   - ext_drop_under:      drop COLD items when fewer than this many free pages
                          (default: 1/4th of the assigned storage)
   - ext_max_frag:        only defrag pages if they are less full than this pct-wise (default: 0.80)
   - ext_max_sleep:       max sleep time of background threads in us (default: 1000000)
   - slab_automove_freeratio: ratio of memory to hold free as buffer.
                          (see doc/storage.txt for more info, default: 0.010)
   - proxy_config:        path to lua library file. separate with ':' for multiple files
                          use proxy_config=routelib to use built-in library
   - proxy_arg:           argument string (file path) to pass to proxy config
   - ssl_chain_cert:      certificate chain file in PEM format
   - ssl_key:             private key, if not part of the -ssl_chain_cert
   - ssl_keyformat:       private key format (PEM, DER or ENGINE) (default: PEM)
   - ssl_verify_mode:     peer certificate verification mode, default is 0(None).
                          valid values are 0(None), 1(Request), 2(Require)
                          or 3(Once)
   - ssl_ciphers:         specify cipher list to be used
   - ssl_ca_cert:         PEM format file of acceptable client CA's
   - ssl_wbuf_size:       size in kilobytes of per-connection SSL output buffer
                          (default: 16)
   - ssl_session_cache:   enable server-side SSL session cache, to support session
                          resumption
   - ssl_kernel_tls:      enable kernel TLS offload
   - ssl_min_version:     minimum protocol version to accept (default: tlsv1.2)
                          valid values are 0(tlsv1.0), 1(tlsv1.1), 2(tlsv1.2), or 3(tlsv1.3).
-N, --napi_ids            number of napi ids. see doc/napi_ids.txt for more details

```
