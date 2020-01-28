#include <gtk/gtk.h>
#include <string.h>

GtkWidget *u_name, *pass, *resultat_assemblage, *resultat_recherche;

void assembler_gtk (GtkWidget *assembler, gpointer data)
{
    char* sequence_final;
    sequence_final = assembler_c();
    gtk_label_set_text(GTK_LABEL(resultat_assemblage),sequence_final);
}

void rechercher_gtk (GtkWidget *rechercher_button, gpointer data)
{
    bool x;
    x=chercher_c(char* sequence_a_chercher);
    if (x==True)
        gtk_label_set_text(GTK_LABEL(resultat_recherche),"Cette sequence existe dans l'ADN");
    else
        gtk_label_set_text(GTK_LABEL(resultat_recherche),"Cette sequence n'existe pas dans l'ADN");
}
void create_window(GtkWidget *Login_button, gpointer data)
{
    GtkWidget *win, *label, *grid2, *assembler, *chercher, *chercher_button, *Quit_button2;
    char* USERNAME = "ensias2020";
    int PASSWORD = 123456;
    int compare;
    char* username = (char*)gtk_entry_get_text(GTK_ENTRY(u_name));
    int password = atoi((char*)gtk_entry_get_text(GTK_ENTRY(pass)));
    compare = strcmp(USERNAME,username);
    if (compare==0)
    {
        if (password==PASSWORD)
        {
            win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_window_set_title(GTK_WINDOW(win), "Assemblage");
            gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
            gtk_container_set_border_width(GTK_CONTAINER(win), 10);

            grid2 = gtk_grid_new();
            gtk_grid_set_row_spacing(GTK_GRID(grid2), 3);
            gtk_container_add(GTK_CONTAINER(win), grid2);

            assembler = gtk_button_new_with_label("Assembler");
            g_signal_connect(assembler, "clicked", G_CALLBACK(assembler_gtk), NULL);
            gtk_grid_attach(GTK_GRID(grid2), assembler, 0, 1, 1, 1);
            resultat_assemblage = gtk_label_new("Resultat:");
            gtk_grid_attach(GTK_GRID(grid2), resultat_assemblage, 1, 1, 2, 1);

            chercher = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(grid2), chercher, 0, 2, 1, 1);
            chercher_button = gtk_button_new_with_label("Chercher");
            g_signal_connect(chercher_button, "clicked", G_CALLBACK(chercher_gtk), NULL);
            gtk_grid_attach(GTK_GRID(grid2), chercher_button, 1, 2, 1, 1);
            resultat_recherche = gtk_label_new("Resultat:");
            gtk_grid_attach(GTK_GRID(grid2), resultat_recherche, 0, 3, 2, 1);
            Quit_button2 = gtk_button_new_with_label("Quitter");
            g_signal_connect(Quit_button2, "clicked", G_CALLBACK(gtk_main_quit), NULL);
            gtk_grid_attach(GTK_GRID(grid2), Quit_button2, 0, 4, 2, 1);

            gtk_widget_show_all(win);
        }
        else
        {
            label = gtk_label_new("Indentifiant ou Mot de passe incorrecte");
            win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_container_add(GTK_CONTAINER(win), label);
            gtk_widget_show_all(win);
        }
    }
    else
    {
        label = gtk_label_new("Indentifiant ou Mot de passe incorrecte.");
        win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_container_add(GTK_CONTAINER(win), label);
        gtk_widget_show_all(win);
    }
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *Login_button, *Quit_button;
    GtkWidget *label_user;
    GtkWidget *label_pass;
    GtkWidget  *button_container;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Identification");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_container_add(GTK_CONTAINER(window), grid);

    label_user = gtk_label_new("Identifiant  ");
    label_pass = gtk_label_new("Mot de passe  ");

    u_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(u_name), "Identifiant");
    gtk_grid_attach(GTK_GRID(grid), label_user, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), u_name, 1, 1, 2, 1);

    pass = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(pass), "Mot de passe");
    gtk_grid_attach(GTK_GRID(grid), label_pass, 0, 2, 1, 1);
    gtk_entry_set_visibility(GTK_ENTRY(pass), 0);
    gtk_grid_attach(GTK_GRID(grid), pass, 1, 2, 1, 1);

    Login_button = gtk_button_new_with_label("Se connecter");
    g_signal_connect(Login_button, "clicked", G_CALLBACK(create_window), NULL);
    gtk_grid_attach(GTK_GRID(grid), Login_button, 0, 3, 2, 1);

    Quit_button = gtk_button_new_with_label("Quitter");
    g_signal_connect(Quit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_grid_attach(GTK_GRID(grid), Quit_button, 0, 4, 2, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
