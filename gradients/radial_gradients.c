#include <cairo.h>
#include <math.h>
#include <gtk/gtk.h>

void draw_gradient1 (cairo_t *);
void draw_gradient2 (cairo_t *);

static gboolean
on_draw_event (GtkWidget *widget,
               cairo_t *cr,
               gpointer user_data)
{
  draw_gradient1 (cr);
  draw_gradient2 (cr);

  return FALSE;
}

void
draw_gradient1 (cairo_t *cr)
{
  cairo_pattern_t *r1;

  cairo_set_source_rgba (cr, 0, 0, 0, 1);
  cairo_set_line_width (cr, 12);
  cairo_translate (cr, 60, 60);

  r1 = cairo_pattern_create_radial (30, 30, 10, 30, 30, 90);
  cairo_pattern_add_color_stop_rgba (r1, 0, 1, 1, 1, 1);
  cairo_pattern_add_color_stop_rgba (r1, 1, 0.6, 0.6, 0.6, 1);
  cairo_set_source (cr, r1);
  cairo_arc (cr, 0, 0, 40, 0, M_PI * 2);
  cairo_fill (cr);

  cairo_pattern_destroy (r1);
}

void
draw_gradient2 (cairo_t *cr)
{
  cairo_pattern_t *r2;

  cairo_translate (cr, 120, 0);

  r2 = cairo_pattern_create_radial (0, 0, 10, 0, 0, 40);
  cairo_pattern_add_color_stop_rgb (r2, 0, 1, 1, 0);
  cairo_pattern_add_color_stop_rgb (r2, 0.8, 0, 0, 0);
  cairo_set_source (cr, r2);
  cairo_arc (cr, 0, 0, 40, 0, M_PI * 2);
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
  g_signal_connect (G_OBJECT (window),
                    "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 200);
  gtk_window_set_title (GTK_WINDOW (window), "Radial gradients");

  gtk_widget_set_app_paintable (window, TRUE);
  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
