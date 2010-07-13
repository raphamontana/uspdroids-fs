/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Soccer Simulator.

    The USPDroids Soccer Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The USPDroids Soccer Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the USPDroids Soccer Simulator.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include "simulator.h"

int main(int argc, char* argv[])
{
    Simulator * uspds;
    int loop;
    loop = 1;
    for (register int i = 1; i < argc; i++) {
        if (!strcmp("-loop", argv[i])) {
            sscanf(argv[++i], "%d", &loop);
        }
        else if (!strcmp("-v", argv[i]) || !strcmp("--version", argv[i])) {
            puts("USPDroids Soccer Simulator version 2.5.0");
            return(0);
        }
        else if (!strcmp("--license", argv[i])) {
            puts("USPDroids Soccer Simulator version 2.5.0\n");
            puts("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n");
            puts("This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n");
            puts("You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.");
            return(0);
        }
        else if (!strcmp("-?", argv[i]) || !strcmp("-h", argv[i]) || !strcmp("--help", argv[i])) {
            printf("Argumento '%s' desconhecido\n", argv[i]);
        } else {
            puts("Uso:");
            puts("  uspds [OPCOES...]\n");
            puts("Simulador de Futebol de Robos\n");
            puts("Opcoes de ajuda:");
            puts("  -?, -h, --help\t\tExibe as opcoes de ajuda");
            puts("Opcoes de aplicativo:");
            puts("  -v, --version\t\t\tExibe informacoes de versao e encerra");
            puts("  --license\t\t\tExibe informacoes sobre a licenca e encerra");
            puts("  -noai1\t\t\tInicia o time 1 sem IA");
            puts("  -noai2\t\t\tInicia o time 2 sem IA");
            puts("  -loop <inteiro>\t\tQuantidade de simulacoess desejadas");
            return(0);
        }
    }
    uspds = new Simulator(26000, 26001, 25999);
    while (loop--) {
        uspds->start();
        //uspds->execute();
        uspds->finish();
    }
    delete(uspds);
    return 0;
}
