# Introdução ao Desenvolvimento de Jogos

Repositório da disciplina **Introdução ao Desenvolvimento de Jogos (IDJ)** – Universidade de Brasília (UnB), semestre **2025.2**.
Professores: Carla Denise Castanho e Eduardo Azevedo.

Este repositório conterá as implementações práticas dos **7 trabalhos cumulativos** da disciplina, que ao final resultarão em um jogo completo.
Cada trabalho será versionado em **releases independentes no GitHub**.

---

## 🎮 Trabalho 1 – Game Loop, Sprite e Music

As principais classes implementadas foram:

- **Game**: responsável pelo *game loop* principal, inicialização da SDL e gerenciamento do estado do jogo (Singleton).
- **State**: define a lógica da tela de jogo, incluindo background, música e condição de saída.
- **Sprite**: responsável pelo carregamento e renderização de imagens.
- **Music**: responsável pelo carregamento e execução de músicas.
- **Main**: ponto de entrada do programa, instanciando `Game` e iniciando a execução.

## 🧟 Trabalho 2 – GameObject, Componentes e Animações

As principais classes e alterações implementadas foram:

- **Rect**: estrutura auxiliar para representar posição e dimensões.
- **Component**: classe base abstrata para encapsular comportamentos de objetos.
- **GameObject**: gerencia um conjunto de componentes, delegando chamadas de `Update` e `Render`.
- **State**: atualizado para armazenar objetos dinamicamente com `std::unique_ptr`, permitindo adicionar e remover `GameObject`s.
- **Sprite**: adaptado para suportar *spritesheets* e animações 2D (múltiplos frames).
- **Animation**: representa uma sequência de frames com tempo de exibição.
- **SpriteRenderer**: componente responsável por desenhar o sprite de um `GameObject`.
- **Zombie**: primeiro inimigo, com pontos de vida e troca de animação ao “morrer”.
- **Animator**: gerencia transições de animação, trocando frames automaticamente.

Essas mudanças permitiram criar o **primeiro personagem animado** do jogo.

## 🧩 Trabalho 3 – TileSet, TileMap e Resource Management

As principais classes e modificações implementadas foram:

- **TileSet**:Responsável por armazenar e recortar tiles a partir de uma imagem base, permitindo renderizar blocos individuais no mapa.
- **TileMap**: Simula uma matriz tridimensional de índices de tiles, controlando as camadas e a disposição dos tiles na tela a partir de um arquivo `map.txt`.
- **Sound**: Classe similar à `Music`, mas voltada a efeitos sonoros curtos. Cada instância controla seu próprio canal de áudio e permite tocar, parar e carregar sons independentes.
- **Resources**: Gerenciador central de recursos do jogo. Mantém tabelas de *hash* (`unordered_map`) que armazenam texturas, músicas e sons já carregados, evitando carregamentos repetidos e liberando memória de forma centralizada.
- **Sprite**: Atualizada para usar o `Resources` em vez de carregar texturas diretamente. Agora, uma mesma imagem é compartilhada entre múltiplos objetos.
- **Zombie**: Agora possui um som de morte (`deathSound`), tocado quando seus pontos de vida chegam a zero.
- **State**: Atualizada para incluir o carregamento de um `TileMap` e a criação de múltiplos zumbis na cena.

## 🕹️ Trabalho 4 – Input, Temporização e Câmera

As principais classes e modificações implementadas foram:

- **InputManager**: singleton responsável por centralizar e abstrair os eventos da SDL. Ele captura e armazena o estado das teclas e botões do mouse, permitindo consultar se uma tecla foi pressionada, solta ou está mantida. Substitui o tratamento direto de eventos nas classes, simplificando o controle de entrada.
- **Timer**: contador de tempo genérico utilizado para medir intervalos (`dt`) entre frames. Serve para controlar animações, delays e lógica temporal no jogo.
- **Game**: adicionados `frameStart`, `dt`, `CalculateDeltaTime()` e `GetDeltaTime()`, permitindo calcular o tempo entre frames e atualizar os objetos proporcionalmente.
- **Camera**: adicionada classe que define a posição da câmera no mundo e controla seu movimento.
- **CameraFollower (SpriteRenderer)**: novo atributo `cameraFollower` para sprites que devem ignorar o deslocamento da câmera (como o background).
- **TileMap – Parallax Scrolling**: implementação de deslocamento diferencial das camadas do mapa, criando efeito de profundidade.

## 🔫 Trabalho 5 – Personagem Jogável, Arma e Projéteis

As principais classes e modificações implementadas foram:

- **Character**: representa o personagem jogável. Possui sistema de comandos que abstrai ações como andar e atirar. Integra animações de idle, movimento e morte, além de gerenciar o estado de vida e interação com a arma.
- **Gun**: componente que representa a arma do personagem. Controla o ciclo de tiro e recarga, reproduzindo sons e animações sincronizados.
- **Bullet**: projétil genérico disparado pela arma. Move-se em linha reta a uma velocidade constante até percorrer uma distância máxima, sendo então removido automaticamente do jogo.
- **PlayerController**: responsável por interpretar as entradas do teclado e mouse, convertendo-as em comandos para o player (movimentação e disparo).
- **Animation (atualização)**: passou a suportar o parâmetro `SDL_RendererFlip`, permitindo espelhar animações horizontalmente ou verticalmente.
- **Sprite / SpriteRenderer (atualização)**: adicionados suporte a rotação (`angleDeg`), escala (`scale`) e espelhamento (`flip`), com renderização via `SDL_RenderCopyEx`.
- **GameObject**: adicionado o atributo `angleDeg` para representar o ângulo de rotação de cada objeto na tela.
- **State**: criação do personagem jogável e de sua arma. Integra o `PlayerController` ao jogador e define o foco da câmera no personagem.

## 👤 Autor

- **Maciel Ferreira Custódio Júnior**
  - Matrícula: 190100087
  - [GitHub](https://github.com/macieljuniormax)
