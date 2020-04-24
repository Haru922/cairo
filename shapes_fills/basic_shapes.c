#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

static void
do_drawing (cairo_t *);

struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;

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
  cairo_set_source_rgb (cr, 0.6, 0.6, 0.6);
  cairo_set_line_width (cr, 1);

  cairo_rectangle (cr, 20, 20, 120, 80);
  cairo_rectangle (cr, 180, 20, 80, 80);
  cairo_stroke_preserve (cr);
  cairo_fill (cr);

  cairo_arc (cr, 330, 60, 40, 0, 2*M_PI);
  cairo_close_path (cr);
  cairo_stroke_preserve (cr);
  cairo_fill (cr);

  cairo_translate (cr, 220, 180);
  cairo_scale (cr, 1, 0.7);
  cairo_arc (cr, 0, 0, 50, 0, 2*M_PI);
  cairo_stroke_preserve (cr);
  cairo_fill (cr);
}

static gboolean
clicked (GtkWidget *widget,
         GdkEventButton *event,
         gpointer user_data)
{
  if (event->button == 1)
  {
    glob.coordx[glob.count] = event->x;
    glob.coordy[glob.count++] = event->y;
  }

  if (event->button == 3)
  {
    gtk_widget_queue_draw (widget);
  }

  return TRUE;
}

int
main (int argc,
      char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  glob.count = 0;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new ();
  gtk_container_add (GTK_CONTAINER (window), darea);

  gtk_widget_add_events (window, GDK_BUTTON_PRESS_MASK);

  g_signal_connect (G_OBJECT (darea), "draw", G_CALLBACK (on_draw_event), NULL);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (window, "button-press-event", G_CALLBACK (clicked), NULL);

  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);
  gtk_window_set_title (GTK_WINDOW (window), "Basic shapes");

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
