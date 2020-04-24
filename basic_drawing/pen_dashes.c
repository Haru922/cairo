#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

static void do_drawing (cairo_t *, GtkWidget *);

static gboolean
on_draw_event (GtkWidget *widget,
               cairo_t *cr,
               gpointer user_data)
{
  do_drawing (cr, widget);

  return FALSE;
}

static void
do_drawing (cairo_t *cr,
            GtkWidget *widget)
{
  cairo_set_source_rgba (cr, 0, 0, 0, 1);

  static const double dashed1[] = { 4.0, 21.0, 2.0 };
  static int len1 = sizeof (dashed1) / sizeof (dashed1[0]);

  static const double dashed2[] = { 14.0, 6.0 };
  static int len2 = sizeof (dashed2) / sizeof (dashed2[0]);

  static const double dashed3[] = { 1.0 };

  cairo_set_line_width (cr, 1.5);

  cairo_set_dash (cr, dashed1, len1, 0);

  cairo_move_to (cr, 40, 30);
  cairo_line_to (cr, 200, 30);
  cairo_stroke (cr);

  cairo_set_dash (cr, dashed2, len2, 1);

  cairo_move_to (cr, 40, 50);
  cairo_line_to (cr, 200, 50);
  cairo_stroke (cr);

  cairo_set_dash (cr, dashed3, 1, 0);

  cairo_move_to (cr, 40, 70);
  cairo_line_to (cr, 200, 70);
  cairo_stroke (cr);
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
  g_signal_connect (G_OBJECT (window),
                    "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 200);
  gtk_window_set_title (GTK_WINDOW (window), "Pen dashes");

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
