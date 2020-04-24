#include <cairo.h>
#include <gtk/gtk.h>

static void do_drawing (cairo_t *);

cairo_surface_t *surface1;
cairo_surface_t *surface2;
cairo_surface_t *surface3;
cairo_surface_t *surface4;

static void
create_surfaces (void)
{
  surface1 = cairo_image_surface_create_from_png ("blueweb.png");
  surface2 = cairo_image_surface_create_from_png ("maple.png");
  surface3 = cairo_image_surface_create_from_png ("crack.png");
  surface4 = cairo_image_surface_create_from_png ("chocolate.png");
}

static void
destroy_surfaces (void)
{
  cairo_surface_destroy (surface1);
  cairo_surface_destroy (surface2);
  cairo_surface_destroy (surface3);
  cairo_surface_destroy (surface4);
}

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
  cairo_pattern_t *pattern1;
  cairo_pattern_t *pattern2;
  cairo_pattern_t *pattern3;
  cairo_pattern_t *pattern4;

  pattern1 = cairo_pattern_create_for_surface (surface1);
  pattern2 = cairo_pattern_create_for_surface (surface2);
  pattern3 = cairo_pattern_create_for_surface (surface3);
  pattern4 = cairo_pattern_create_for_surface (surface4);

  cairo_set_source (cr, pattern1);
  cairo_pattern_set_extend (cairo_get_source (cr), CAIRO_EXTEND_REPEAT);
  cairo_rectangle (cr, 20, 20, 100, 100);
  cairo_fill (cr);

  cairo_set_source (cr, pattern2);
  cairo_pattern_set_extend (cairo_get_source (cr), CAIRO_EXTEND_REPEAT);
  cairo_rectangle (cr, 150, 20, 100, 100);
  cairo_fill (cr);

  cairo_set_source (cr, pattern3);
  cairo_pattern_set_extend (cairo_get_source (cr), CAIRO_EXTEND_REPEAT);
  cairo_rectangle (cr, 20, 140, 100, 100);
  cairo_fill (cr);

  cairo_set_source (cr, pattern4);
  cairo_pattern_set_extend (cairo_get_source (cr), CAIRO_EXTEND_REPEAT);
  cairo_rectangle (cr, 150, 140, 100, 100);
  cairo_fill (cr);

  cairo_pattern_destroy (pattern1);
  cairo_pattern_destroy (pattern2);
  cairo_pattern_destroy (pattern3);
  cairo_pattern_destroy (pattern4);
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

  create_surfaces ();

  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 270, 260);
  gtk_window_set_title (GTK_WINDOW (window), "Patterns");

  gtk_widget_show_all (window);

  gtk_main ();

  destroy_surfaces ();

  return 0;
}
