## サーバー起動準備

```mermaid
graph TD
    A[サーバー起動] --> B[/Try Brock\]
    B --> C{poll}
    C -- POLLIN --> D{POLLINはサーバか}
    D -- Yes --> E[accept]
    D -- No --> F[recv]
```

