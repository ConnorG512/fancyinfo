{
  description = "Fancy Info flake.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let 
    system = "x86_64-linux";
    pkgs =  import nixpkgs { inherit system; };
  in {
     devShells.x86_64-linux.default = pkgs.mkShell {
        packages = with pkgs; [
          ccls
          cmake 
          ninja
        ];

        shellHook = ''
          echo "Fancy flake shell entered!"
        '';
      };

    packages.x86_64-linux.default = pkgs.stdenv.mkDerivation {
      name = "Fancy Info";
      pname = "finfo";
      version = "0.1.0";
      src = ./.;

      nativeBuildInputs = with pkgs; [
        cmake 
        ninja
      ];
      configurePhase = ''
        cmake -B build -S . -G Ninja
      '';
      buildPhase = ''
        cmake --build build
      '';
      installPhase = ''
        mkdir -p $out/bin
        cp build/finfo $out/bin
      '';
    };
  };
}
