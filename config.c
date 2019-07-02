#include <stdio.h>
#include <string.h>

const char mod[] = "Mod4";

struct sym{
	_Bool mod;
	char key[100];
	char command[100];
};

void bindsym(struct sym *s){
	printf("bindsym ");
	if(s->mod) printf("%s+", mod);
	printf("%s %s\n", s->key, s->command);
}

struct sym global[] = {
	{
		.mod = 1,
		.key = "Return",
		.command = "exec terminator"
	},{
		.mod = 1,
		.key = "space",
		.command = "exec rofi -show run"
	},{
		.mod = 1,
		.key = "Delete",
		.command = "kill"
	}
};

struct mode{
	char name[1000];
	char key[100];
	_Bool description;
	struct sym sym[100];
};

void desc(struct mode *m){
	for(int i = 0; m->sym[i].key[0]; ++i) sprintf(m->name + strlen(m->name), " [%s : %s]", m->sym[i].key, m->sym[i].command);
}

struct mode mode[] = {
	{
		.name = "exit",
		.key = "Shift+e",
		.description = 1,
		.sym = {
			{
				.key = "e",
				.command = "exit"
			},{
				.key = "r",
				.command = "restart"
			},{
				.key = "w",
				.command = "reload"
			}
		}
	},{
		.name = "split",
		.key = "s",
		.description = 1,
		.sym = {
			{
				.key = "v",
				.command = "split vertical"
			},{
				.key = "h",
				.command = "split horizontal"
			},{
				.key = "t",
				.command = "split toggle"
			}
		}
	},{
		.name = "layout",
		.key = "l",
		.description = 1,
		.sym = {
			{
				.key = "d",
				.command = "layout default"
			},{
				.key = "t",
				.command = "layout tabbed"
			},{
				.key = "s",
				.command = "layout stacking"
			},{
				.key = "v",
				.command = "layout splitv"
			},{
				.key = "h",
				.command = "layout splith"
			},{
				.key = "f",
				.command = "fullscreen toggle"
			},{
				.key = "Shift+f",
				.command = "floating toggle"
			}
		}
	},{
		.name = "focus",
		.key = "f",
		.description = 1,
		.sym = {
			{
				.key = "h",
				.command = "focus left"
			},{
				.key = "j",
				.command = "focus down"
			},{
				.key = "k",
				.command = "focus up"
			},{
				.key = "l",
				.command = "focus right"
			},{
				.key = "p",
				.command = "focus parent"
			},{
				.key = "f",
				.command = "focus mode_toggle"
			}
		}
	},{
		.name = "move",
		.key = "m",
		.description = 1,
		.sym = {
			{
				.key = "h",
				.command = "move left"
			},{
				.key = "j",
				.command = "move down"
			},{
				.key = "k",
				.command = "move up"
			},{
				.key = "l",
				.command = "move right"
			},{
				.key = "c",
				.command = "move absolute position center"
			},{
				.key = "m",
				.command = "move position mouse"
			}
		}
	},{
		.name = "sticky",
		.key = "Shift+s",
		.description = 1,
		.sym = {
			{
				.key = "e",
				.command = "sticky enable"
			},{
				.key = "d",
				.command = "sticky disable"
			},{
				.key = "t",
				.command = "sticky toggle"
			}
		}
	},{
		.name = "resize",
		.key = "r",
		.description = 1,
		.sym = {
			{
				.key = "h",
				.command = "resize shrink width"
			},{
				.key = "j",
				.command = "resize grow height"
			},{
				.key = "k",
				.command = "resize shrink height"
			},{
				.key = "l",
				.command = "resize grow width"
			}
		}
	},{
		.name = "border",
		.key = "b",
		.description = 1,
		.sym = {
			{
				.key = "n",
				.command = "border normal"
			},{
				.key = "p",
				.command = "border pixel"
			},{
				.key = "Shift+n",
				.command = "border none"
			}
		}
	},{
		.name = "workspace",
		.key = "w",
		.description = 0,
	}
};

void switch_to_mode(struct mode *m){
	printf("bindsym %s+%s mode \"%s\"\n", mod, m->key, m->name);
}

void set_workspace(){
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) if(!strcmp(mode[i].name, "workspace")){
		for(int j = 0; j < 10; ++j){
			sprintf(mode[i].sym[j * 2].key, "%d", j);
			sprintf(mode[i].sym[j * 2].command, "workspace %d", j);
			sprintf(mode[i].sym[j * 2 + 1].key, "Shift+%d", j);
			sprintf(mode[i].sym[j * 2 + 1].command, "move container to workspace %d", j);
		}
		for(int j = 0; j < 26; ++j){
			sprintf(mode[i].sym[j * 2 + 20].key, "%c", 'A' + j);
			sprintf(mode[i].sym[j * 2 + 20].command, "workspace %c", 'A' + j);
			sprintf(mode[i].sym[j * 2 + 21].key, "Shift+%c", 'A' + j);
			sprintf(mode[i].sym[j * 2 + 21].command, "move container to workspace %c", 'A' + j);
		}
	}
}

void print_mode(struct mode *m){
	printf("mode \"%s\"{\nbindsym Return mode \"default\"\n", m->name);
	for(int i = 0; i < sizeof global / sizeof global[0]; ++i) bindsym(global + i);
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) if(mode + i != m) switch_to_mode(mode + i);
	for(int i = 0; m->sym[i].key[0]; ++i) bindsym(m->sym + i);
	printf("}\n");
}

int main(){
	for(int i = 0; i < sizeof global / sizeof global[0]; ++i) bindsym(global + i);
	printf("bar{\nstatus_command i3status\n}\n");
	set_workspace();
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) if(mode[i].description) desc(mode + i);
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) switch_to_mode(mode + i);
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) print_mode(mode + i);
}
