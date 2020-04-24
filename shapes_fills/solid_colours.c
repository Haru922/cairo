#include <cairo.h>
#include <gtk/gtk.h>

static void do_drawing (cairo_t *);

static gboolean
on_draw_event (GtkWidget *widget,
               cairo_t *cr,
               gpointer user_data)
{
  do_drawing (cr);

  return FALSE;
}

static void
do_drawing (cairo_t *cr)
{
  cairo_set_source_rgb (cr, 0.5, 0.5, 1);
  cairo_rectangle (cr, 20, 20, 100, 100);
  cairo_fill (cr);

  cairo_set_source_rgb (cr, 0.6, 0.6, 0.6);
  cairo_rectangle (cr, 150, 20, 100, 100);
  cairo_fill (cr);

  cairo_set_source_rgb (cr, 0, 0.3, 0);
  cairo_rectangle (cr, 20, 140, 100, 100);
  cairo_fill (cr);

  cairo_set_source_rgb (cr, 1, 0, 0.5);
  cairo_rectangle (cr, 150, 140, 100, 100);
  cairo_fill (cr);
}

int
main (int argc,
      char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new ();
  gtk_container_add (GTK_CONTAINER (window), darea);

  g_signal_connect (G_OBJECT (darea),
                    "draw",
                    G_CALLBACK (on_draw_event),
                    NULL);
  g_signal_connect (window,
                    "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 460, 240);
  gtk_window_set_title (GTK_WINDOW (window), "Solid colours");

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
