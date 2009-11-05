package yunikorn.core.packet.metainterfaces;

public interface PacketObservable<T extends PacketListener> {
	public void addListener(T listener);
	public void removeListener(T listener);
}
